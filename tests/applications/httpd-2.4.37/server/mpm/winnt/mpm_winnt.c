/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef WIN32

#include "httpd.h"
#include "http_main.h"
#include "http_log.h"
#include "http_config.h" /* for read_config */
#include "http_core.h"   /* for get_remote_host */
#include "http_connection.h"
#include "apr_portable.h"
#include "apr_thread_proc.h"
#include "apr_getopt.h"
#include "apr_strings.h"
#include "apr_lib.h"
#include "apr_shm.h"
#include "apr_thread_mutex.h"
#include "ap_mpm.h"
#include "apr_general.h"
#include "ap_config.h"
#include "ap_listen.h"
#include "mpm_default.h"
#include "mpm_winnt.h"
#include "mpm_common.h"
#include <malloc.h>
#include "apr_atomic.h"
#include "scoreboard.h"

#ifdef __WATCOMC__
#define _environ environ
#endif

#ifndef STACK_SIZE_PARAM_IS_A_RESERVATION /* missing on MinGW */
#define STACK_SIZE_PARAM_IS_A_RESERVATION 0x00010000
#endif

/* Because ap_setup_listeners() is skipped in the child, any merging
 * of [::]:80 and 0.0.0.0:80 for AP_ENABLE_V4_MAPPED in the parent
 * won't have taken place in the child, so the child will expect to
 * read two sockets for "Listen 80" but the parent will send only
 * one.
 */
#ifdef AP_ENABLE_V4_MAPPED
#error The WinNT MPM does not currently support AP_ENABLE_V4_MAPPED
#endif

/* scoreboard.c does the heavy lifting; all we do is create the child
 * score by moving a handle down the pipe into the child's stdin.
 */
extern apr_shm_t *ap_scoreboard_shm;

/* my_generation is returned to the scoreboard code */
static volatile ap_generation_t my_generation=0;

/* Definitions of WINNT MPM specific config globals */
static HANDLE shutdown_event;  /* used to signal the parent to shutdown */
static HANDLE restart_event;   /* used to signal the parent to restart */

static int one_process = 0;
static char const* signal_arg = NULL;

OSVERSIONINFO osver; /* VER_PLATFORM_WIN32_NT */

/* set by child_main to STACK_SIZE_PARAM_IS_A_RESERVATION for NT >= 5.1 (XP/2003) */
DWORD stack_res_flag;

static DWORD parent_pid;
DWORD my_pid;

/* used by parent to signal the child to start and exit */
apr_proc_mutex_t *start_mutex;
HANDLE exit_event;

int ap_threads_per_child = 0;
static int thread_limit = 0;
static int first_thread_limit = 0;
int winnt_mpm_state = AP_MPMQ_STARTING;

/* shared by service.c as global, although
 * perhaps it should be private.
 */
apr_pool_t *pconf;

/* Only one of these, the pipe from our parent, meant only for
 * one child worker's consumption (not to be inherited!)
 * XXX: decorate this name for the trunk branch, was left simplified
 *      only to make the 2.2 patch trivial to read.
 */
static HANDLE pipe;

/*
 * Command processors
 */

static const char *set_threads_per_child (cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_threads_per_child = atoi(arg);
    return NULL;
}
static const char *set_thread_limit (cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    thread_limit = atoi(arg);
    return NULL;
}

static const command_rec winnt_cmds[] = {
LISTEN_COMMANDS,
AP_INIT_TAKE1("ThreadsPerChild", set_threads_per_child, NULL, RSRC_CONF,
  "Number of threads each child creates" ),
AP_INIT_TAKE1("ThreadLimit", set_thread_limit, NULL, RSRC_CONF,
  "Maximum worker threads in a server for this run of Apache"),
{ NULL }
};

static void winnt_note_child_started(int slot, pid_t pid)
{
    ap_scoreboard_image->parent[slot].pid = pid;
    ap_scoreboard_image->parent[slot].generation = my_generation;
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        my_generation, slot, MPM_CHILD_STARTED);
}

static void winnt_note_child_killed(int slot)
{
    ap_run_child_status(ap_server_conf,
                        ap_scoreboard_image->parent[slot].pid,
                        ap_scoreboard_image->parent[slot].generation,
                        slot, MPM_CHILD_EXITED);
    ap_scoreboard_image->parent[slot].pid = 0;
}

/*
 * Signalling Apache on NT.
 *
 * Under Unix, Apache can be told to shutdown or restart by sending various
 * signals (HUP, USR, TERM). On NT we don't have easy access to signals, so
 * we use "events" instead. The parent apache process goes into a loop
 * where it waits forever for a set of events. Two of those events are
 * called
 *
 *    apPID_shutdown
 *    apPID_restart
 *
 * (where PID is the PID of the apache parent process). When one of these
 * is signalled, the Apache parent performs the appropriate action. The events
 * can become signalled through internal Apache methods (e.g. if the child
 * finds a fatal error and needs to kill its parent), via the service
 * control manager (the control thread will signal the shutdown event when
 * requested to stop the Apache service), from the -k Apache command line,
 * or from any external program which finds the Apache PID from the
 * httpd.pid file.
 *
 * The signal_parent() function, below, is used to signal one of these events.
 * It can be called by any child or parent process, since it does not
 * rely on global variables.
 *
 * On entry, type gives the event to signal. 0 means shutdown, 1 means
 * graceful restart.
 */
/*
 * Initialise the signal names, in the global variables signal_name_prefix,
 * signal_restart_name and signal_shutdown_name.
 */
#define MAX_SIGNAL_NAME 30  /* Long enough for apPID_shutdown, where PID is an int */
static char signal_name_prefix[MAX_SIGNAL_NAME];
static char signal_restart_name[MAX_SIGNAL_NAME];
static char signal_shutdown_name[MAX_SIGNAL_NAME];
static void setup_signal_names(char *prefix)
{
    apr_snprintf(signal_name_prefix, sizeof(signal_name_prefix), prefix);
    apr_snprintf(signal_shutdown_name, sizeof(signal_shutdown_name),
        "%s_shutdown", signal_name_prefix);
    apr_snprintf(signal_restart_name, sizeof(signal_restart_name),
        "%s_restart", signal_name_prefix);
}

AP_DECLARE(void) ap_signal_parent(ap_signal_parent_e type)
{
    HANDLE e;
    char *signal_name;

    if (parent_pid == my_pid) {
        switch(type) {
           case SIGNAL_PARENT_SHUTDOWN:
           {
               SetEvent(shutdown_event);
               break;
           }
           /* This MPM supports only graceful restarts right now */
           case SIGNAL_PARENT_RESTART:
           case SIGNAL_PARENT_RESTART_GRACEFUL:
           {
               SetEvent(restart_event);
               break;
           }
        }
        return;
    }

    switch(type) {
       case SIGNAL_PARENT_SHUTDOWN:
       {
           signal_name = signal_shutdown_name;
           break;
       }
       /* This MPM supports only graceful restarts right now */
       case SIGNAL_PARENT_RESTART:
       case SIGNAL_PARENT_RESTART_GRACEFUL:
       {
           signal_name = signal_restart_name;
           break;
       }
       default:
           return;
    }

    e = OpenEvent(EVENT_MODIFY_STATE, FALSE, signal_name);
    if (!e) {
        /* Um, problem, can't signal the parent, which means we can't
         * signal ourselves to die. Ignore for now...
         */
        ap_log_error(APLOG_MARK, APLOG_EMERG, apr_get_os_error(), ap_server_conf, APLOGNO(00382)
                     "OpenEvent on %s event", signal_name);
        return;
    }
    if (SetEvent(e) == 0) {
        /* Same problem as above */
        ap_log_error(APLOG_MARK, APLOG_EMERG, apr_get_os_error(), ap_server_conf, APLOGNO(00383)
                     "SetEvent on %s event", signal_name);
        CloseHandle(e);
        return;
    }
    CloseHandle(e);
}


/*
 * Passed the following handles [in sync with send_handles_to_child()]
 *
 *   ready event [signal the parent immediately, then close]
 *   exit event  [save to poll later]
 *   start mutex [signal from the parent to begin accept()]
 *   scoreboard shm handle [to recreate the ap_scoreboard]
 */
static void get_handles_from_parent(server_rec *s, HANDLE *child_exit_event,
                                    apr_proc_mutex_t **child_start_mutex,
                                    apr_shm_t **scoreboard_shm)
{
    HANDLE hScore;
    HANDLE ready_event;
    HANDLE os_start;
    DWORD BytesRead;
    void *sb_shared;
    apr_status_t rv;

    /* *** We now do this way back in winnt_rewrite_args
     * pipe = GetStdHandle(STD_INPUT_HANDLE);
     */
    if (!ReadFile(pipe, &ready_event, sizeof(HANDLE),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(HANDLE))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00384)
                     "Child: Unable to retrieve the ready event from the parent");
        exit(APEXIT_CHILDINIT);
    }

    SetEvent(ready_event);
    CloseHandle(ready_event);

    if (!ReadFile(pipe, child_exit_event, sizeof(HANDLE),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(HANDLE))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00385)
                     "Child: Unable to retrieve the exit event from the parent");
        exit(APEXIT_CHILDINIT);
    }

    if (!ReadFile(pipe, &os_start, sizeof(os_start),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(os_start))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00386)
                     "Child: Unable to retrieve the start_mutex from the parent");
        exit(APEXIT_CHILDINIT);
    }
    *child_start_mutex = NULL;
    if ((rv = apr_os_proc_mutex_put(child_start_mutex, &os_start, s->process->pool))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00387)
                     "Child: Unable to access the start_mutex from the parent");
        exit(APEXIT_CHILDINIT);
    }

    if (!ReadFile(pipe, &hScore, sizeof(hScore),
                  &BytesRead, (LPOVERLAPPED) NULL)
        || (BytesRead != sizeof(hScore))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00388)
                     "Child: Unable to retrieve the scoreboard from the parent");
        exit(APEXIT_CHILDINIT);
    }
    *scoreboard_shm = NULL;
    if ((rv = apr_os_shm_put(scoreboard_shm, &hScore, s->process->pool))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00389)
                     "Child: Unable to access the scoreboard from the parent");
        exit(APEXIT_CHILDINIT);
    }

    rv = ap_reopen_scoreboard(s->process->pool, scoreboard_shm, 1);
    if (rv || !(sb_shared = apr_shm_baseaddr_get(*scoreboard_shm))) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00390)
                     "Child: Unable to reopen the scoreboard from the parent");
        exit(APEXIT_CHILDINIT);
    }
    /* We must 'initialize' the scoreboard to relink all the
     * process-local pointer arrays into the shared memory block.
     */
    ap_init_scoreboard(sb_shared);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00391)
                 "Child: Retrieved our scoreboard from the parent.");
}


static int send_handles_to_child(apr_pool_t *p,
                                 HANDLE child_ready_event,
                                 HANDLE child_exit_event,
                                 apr_proc_mutex_t *child_start_mutex,
                                 apr_shm_t *scoreboard_shm,
                                 HANDLE hProcess,
                                 apr_file_t *child_in)
{
    apr_status_t rv;
    HANDLE hCurrentProcess = GetCurrentProcess();
    HANDLE hDup;
    HANDLE os_start;
    HANDLE hScore;
    apr_size_t BytesWritten;

    if ((rv = apr_file_write_full(child_in, &my_generation,
                                  sizeof(my_generation), NULL))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(02964)
                     "Parent: Unable to send its generation to the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, child_ready_event, hProcess, &hDup,
        EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00392)
                     "Parent: Unable to duplicate the ready event handle for the child");
        return -1;
    }
    if ((rv = apr_file_write_full(child_in, &hDup, sizeof(hDup), &BytesWritten))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00393)
                     "Parent: Unable to send the exit event handle to the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, child_exit_event, hProcess, &hDup,
                         EVENT_MODIFY_STATE | SYNCHRONIZE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00394)
                     "Parent: Unable to duplicate the exit event handle for the child");
        return -1;
    }
    if ((rv = apr_file_write_full(child_in, &hDup, sizeof(hDup), &BytesWritten))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00395)
                     "Parent: Unable to send the exit event handle to the child");
        return -1;
    }
    if ((rv = apr_os_proc_mutex_get(&os_start, child_start_mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00396)
                     "Parent: Unable to retrieve the start mutex for the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, os_start, hProcess, &hDup,
                         SYNCHRONIZE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00397)
                     "Parent: Unable to duplicate the start mutex to the child");
        return -1;
    }
    if ((rv = apr_file_write_full(child_in, &hDup, sizeof(hDup), &BytesWritten))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00398)
                     "Parent: Unable to send the start mutex to the child");
        return -1;
    }
    if ((rv = apr_os_shm_get(&hScore, scoreboard_shm)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00399)
                     "Parent: Unable to retrieve the scoreboard handle for the child");
        return -1;
    }
    if (!DuplicateHandle(hCurrentProcess, hScore, hProcess, &hDup,
                         FILE_MAP_READ | FILE_MAP_WRITE, FALSE, 0)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00400)
                     "Parent: Unable to duplicate the scoreboard handle to the child");
        return -1;
    }
    if ((rv = apr_file_write_full(child_in, &hDup, sizeof(hDup), &BytesWritten))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00401)
                     "Parent: Unable to send the scoreboard handle to the child");
        return -1;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00402)
                 "Parent: Sent the scoreboard to the child");
    return 0;
}


/*
 * get_listeners_from_parent()
 * The listen sockets are opened in the parent. This function, which runs
 * exclusively in the child process, receives them from the parent and
 * makes them availeble in the child.
 */
static void get_listeners_from_parent(server_rec *s)
{
    WSAPROTOCOL_INFO WSAProtocolInfo;
    ap_listen_rec *lr;
    DWORD BytesRead;
    int lcnt = 0;
    SOCKET nsd;

    /* Set up a default listener if necessary */
    if (ap_listeners == NULL) {
        ap_listen_rec *lr;
        lr = apr_palloc(s->process->pool, sizeof(ap_listen_rec));
        lr->sd = NULL;
        lr->next = ap_listeners;
        ap_listeners = lr;
    }

    /* Open the pipe to the parent process to receive the inherited socket
     * data. The sockets have been set to listening in the parent process.
     *
     * *** We now do this way back in winnt_rewrite_args
     * pipe = GetStdHandle(STD_INPUT_HANDLE);
     */
    for (lr = ap_listeners; lr; lr = lr->next, ++lcnt) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00403)
                     "Child: Waiting for data for listening socket %pI",
                     lr->bind_addr);
        if (!ReadFile(pipe, &WSAProtocolInfo, sizeof(WSAPROTOCOL_INFO),
                      &BytesRead, (LPOVERLAPPED) NULL)) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00404)
                         "Child: Unable to read socket data from parent");
            exit(APEXIT_CHILDINIT);
        }

        nsd = WSASocket(FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO, FROM_PROTOCOL_INFO,
                        &WSAProtocolInfo, 0, 0);
        if (nsd == INVALID_SOCKET) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf, APLOGNO(00405)
                         "Child: WSASocket failed to open the inherited socket");
            exit(APEXIT_CHILDINIT);
        }

        if (!SetHandleInformation((HANDLE)nsd, HANDLE_FLAG_INHERIT, 0)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), ap_server_conf, APLOGNO(00406)
                         "Child: SetHandleInformation failed");
        }
        apr_os_sock_put(&lr->sd, &nsd, s->process->pool);
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00407)
                 "Child: retrieved %d listeners from parent", lcnt);
}


static int send_listeners_to_child(apr_pool_t *p, DWORD dwProcessId,
                                   apr_file_t *child_in)
{
    apr_status_t rv;
    int lcnt = 0;
    ap_listen_rec *lr;
    LPWSAPROTOCOL_INFO  lpWSAProtocolInfo;
    apr_size_t BytesWritten;

    /* Run the chain of open sockets. For each socket, duplicate it
     * for the target process then send the WSAPROTOCOL_INFO
     * (returned by dup socket) to the child.
     */
    for (lr = ap_listeners; lr; lr = lr->next, ++lcnt) {
        apr_os_sock_t nsd;
        lpWSAProtocolInfo = apr_pcalloc(p, sizeof(WSAPROTOCOL_INFO));
        apr_os_sock_get(&nsd, lr->sd);
        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00408)
                     "Parent: Duplicating socket %d (%pI) and sending it to child process %lu",
                     nsd, lr->bind_addr, dwProcessId);
        if (WSADuplicateSocket(nsd, dwProcessId,
                               lpWSAProtocolInfo) == SOCKET_ERROR) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), ap_server_conf, APLOGNO(00409)
                         "Parent: WSADuplicateSocket failed for socket %d. Check the FAQ.", nsd);
            return -1;
        }

        if ((rv = apr_file_write_full(child_in, lpWSAProtocolInfo,
                                      sizeof(WSAPROTOCOL_INFO), &BytesWritten))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00410)
                         "Parent: Unable to write duplicated socket %d to the child.", nsd);
            return -1;
        }
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00411)
                 "Parent: Sent %d listeners to child %lu", lcnt, dwProcessId);
    return 0;
}

enum waitlist_e {
    waitlist_ready = 0,
    waitlist_term = 1
};

static int create_process(apr_pool_t *p, HANDLE *child_proc, HANDLE *child_exit_event,
                          DWORD *child_pid)
{
    /* These NEVER change for the lifetime of this parent
     */
    static char **args = NULL;
    static char pidbuf[28];

    apr_status_t rv;
    apr_pool_t *ptemp;
    apr_procattr_t *attr;
    apr_proc_t new_child;
    HANDLE hExitEvent;
    HANDLE waitlist[2];  /* see waitlist_e */
    char *cmd;
    char *cwd;
    char **env;
    int envc;

    apr_pool_create_ex(&ptemp, p, NULL, NULL);

    /* Build the command line. Should look something like this:
     * C:/apache/bin/httpd.exe -f ap_server_confname
     * First, get the path to the executable...
     */
    apr_procattr_create(&attr, ptemp);
    apr_procattr_cmdtype_set(attr, APR_PROGRAM);
    apr_procattr_detach_set(attr, 1);
    if (((rv = apr_filepath_get(&cwd, 0, ptemp)) != APR_SUCCESS)
           || ((rv = apr_procattr_dir_set(attr, cwd)) != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00412)
                     "Parent: Failed to get the current path");
    }

    if (!args) {
        /* Build the args array, only once since it won't change
         * for the lifetime of this parent process.
         */
        if ((rv = ap_os_proc_filepath(&cmd, ptemp))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, ERROR_BAD_PATHNAME, ap_server_conf, APLOGNO(00413)
                         "Parent: Failed to get full path of %s",
                         ap_server_conf->process->argv[0]);
            apr_pool_destroy(ptemp);
            return -1;
        }

        args = malloc((ap_server_conf->process->argc + 1) * sizeof (char*));
        memcpy(args + 1, ap_server_conf->process->argv + 1,
               (ap_server_conf->process->argc - 1) * sizeof (char*));
        args[0] = malloc(strlen(cmd) + 1);
        strcpy(args[0], cmd);
        args[ap_server_conf->process->argc] = NULL;
    }
    else {
        cmd = args[0];
    }

    /* Create a pipe to send handles to the child */
    if ((rv = apr_procattr_io_set(attr, APR_FULL_BLOCK,
                                  APR_NO_PIPE, APR_NO_PIPE)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00414)
                        "Parent: Unable to create child stdin pipe.");
        apr_pool_destroy(ptemp);
        return -1;
    }

    /* Create the child_ready_event */
    waitlist[waitlist_ready] = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!waitlist[waitlist_ready]) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00415)
                     "Parent: Could not create ready event for child process");
        apr_pool_destroy (ptemp);
        return -1;
    }

    /* Create the child_exit_event */
    hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!hExitEvent) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00416)
                     "Parent: Could not create exit event for child process");
        apr_pool_destroy(ptemp);
        CloseHandle(waitlist[waitlist_ready]);
        return -1;
    }

    /* Build the env array */
    for (envc = 0; _environ[envc]; ++envc) {
        ;
    }
    env = apr_palloc(ptemp, (envc + 2) * sizeof (char*));
    memcpy(env, _environ, envc * sizeof (char*));
    apr_snprintf(pidbuf, sizeof(pidbuf), "AP_PARENT_PID=%lu", parent_pid);
    env[envc] = pidbuf;
    env[envc + 1] = NULL;

    rv = apr_proc_create(&new_child, cmd, (const char * const *)args,
                         (const char * const *)env, attr, ptemp);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00417)
                     "Parent: Failed to create the child process.");
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(waitlist[waitlist_ready]);
        CloseHandle(new_child.hproc);
        return -1;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00418)
                 "Parent: Created child process %d", new_child.pid);

    if (send_handles_to_child(ptemp, waitlist[waitlist_ready], hExitEvent,
                              start_mutex, ap_scoreboard_shm,
                              new_child.hproc, new_child.in)) {
        /*
         * This error is fatal, mop up the child and move on
         * We toggle the child's exit event to cause this child
         * to quit even as it is attempting to start.
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(waitlist[waitlist_ready]);
        CloseHandle(new_child.hproc);
        return -1;
    }

    /* Important:
     * Give the child process a chance to run before dup'ing the sockets.
     * We have already set the listening sockets noninheritable, but if
     * WSADuplicateSocket runs before the child process initializes
     * the listeners will be inherited anyway.
     */
    waitlist[waitlist_term] = new_child.hproc;
    rv = WaitForMultipleObjects(2, waitlist, FALSE, INFINITE);
    CloseHandle(waitlist[waitlist_ready]);
    if (rv != WAIT_OBJECT_0) {
        /*
         * Outch... that isn't a ready signal. It's dead, Jim!
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(new_child.hproc);
        return -1;
    }

    if (send_listeners_to_child(ptemp, new_child.pid, new_child.in)) {
        /*
         * This error is fatal, mop up the child and move on
         * We toggle the child's exit event to cause this child
         * to quit even as it is attempting to start.
         */
        SetEvent(hExitEvent);
        apr_pool_destroy(ptemp);
        CloseHandle(hExitEvent);
        CloseHandle(new_child.hproc);
        return -1;
    }

    apr_file_close(new_child.in);

    *child_exit_event = hExitEvent;
    *child_proc = new_child.hproc;
    *child_pid = new_child.pid;

    return 0;
}

/***********************************************************************
 * master_main()
 * master_main() runs in the parent process.  It creates the child
 * process which handles HTTP requests then waits on one of three
 * events:
 *
 * restart_event
 * -------------
 * The restart event causes master_main to start a new child process and
 * tells the old child process to exit (by setting the child_exit_event).
 * The restart event is set as a result of one of the following:
 * 1. An apache -k restart command on the command line
 * 2. A command received from Windows service manager which gets
 *    translated into an ap_signal_parent(SIGNAL_PARENT_RESTART)
 *    call by code in service.c.
 * 3. The child process calling ap_signal_parent(SIGNAL_PARENT_RESTART)
 *    as a result of hitting MaxConnectionsPerChild.
 *
 * shutdown_event
 * --------------
 * The shutdown event causes master_main to tell the child process to
 * exit and that the server is shutting down. The shutdown event is
 * set as a result of one of the following:
 * 1. An apache -k shutdown command on the command line
 * 2. A command received from Windows service manager which gets
 *    translated into an ap_signal_parent(SIGNAL_PARENT_SHUTDOWN)
 *    call by code in service.c.
 *
 * child process handle
 * --------------------
 * The child process handle will be signaled if the child process
 * exits for any reason. In a normal running server, the signaling
 * of this event means that the child process has exited prematurely
 * due to a seg fault or other irrecoverable error. For server
 * robustness, master_main will restart the child process under this
 * condtion.
 *
 * master_main uses the child_exit_event to signal the child process
 * to exit.
 **********************************************************************/
#define NUM_WAIT_HANDLES 3
#define CHILD_HANDLE     0
#define SHUTDOWN_HANDLE  1
#define RESTART_HANDLE   2
static int master_main(server_rec *s, HANDLE shutdown_event, HANDLE restart_event)
{
    int rv, cld;
    int child_created;
    int restart_pending;
    int shutdown_pending;
    HANDLE child_exit_event;
    HANDLE event_handles[NUM_WAIT_HANDLES];
    DWORD child_pid;

    child_created = restart_pending = shutdown_pending = 0;

    event_handles[SHUTDOWN_HANDLE] = shutdown_event;
    event_handles[RESTART_HANDLE] = restart_event;

    /* Create a single child process */
    rv = create_process(pconf, &event_handles[CHILD_HANDLE],
                        &child_exit_event, &child_pid);
    if (rv < 0)
    {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00419)
                     "master_main: create child process failed. Exiting.");
        shutdown_pending = 1;
        goto die_now;
    }

    child_created = 1;

    if (!strcasecmp(signal_arg, "runservice")) {
        mpm_service_started();
    }

    /* Update the scoreboard. Note that there is only a single active
     * child at once.
     */
    ap_scoreboard_image->parent[0].quiescing = 0;
    winnt_note_child_started(/* slot */ 0, child_pid);

    /* Wait for shutdown or restart events or for child death */
    winnt_mpm_state = AP_MPMQ_RUNNING;
    rv = WaitForMultipleObjects(NUM_WAIT_HANDLES, (HANDLE *) event_handles, FALSE, INFINITE);
    cld = rv - WAIT_OBJECT_0;
    if (rv == WAIT_FAILED) {
        /* Something serious is wrong */
        ap_log_error(APLOG_MARK,APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00420)
                     "master_main: WaitForMultipleObjects WAIT_FAILED -- doing server shutdown");
        shutdown_pending = 1;
    }
    else if (rv == WAIT_TIMEOUT) {
        /* Hey, this cannot happen */
        ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00421)
                     "master_main: WaitForMultipleObjects with INFINITE wait exited with WAIT_TIMEOUT");
        shutdown_pending = 1;
    }
    else if (cld == SHUTDOWN_HANDLE) {
        /* shutdown_event signalled */
        shutdown_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, s, APLOGNO(00422)
                     "Parent: Received shutdown signal -- Shutting down the server.");
        if (ResetEvent(shutdown_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00423)
                         "ResetEvent(shutdown_event)");
        }
    }
    else if (cld == RESTART_HANDLE) {
        /* Received a restart event. Prepare the restart_event to be reused
         * then signal the child process to exit.
         */
        restart_pending = 1;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, APLOGNO(00424)
                     "Parent: Received restart signal -- Restarting the server.");
        if (ResetEvent(restart_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00425)
                         "Parent: ResetEvent(restart_event) failed.");
        }
        if (SetEvent(child_exit_event) == 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, apr_get_os_error(), s, APLOGNO(00426)
                         "Parent: SetEvent for child process event %pp failed.",
                         event_handles[CHILD_HANDLE]);
        }
        /* Don't wait to verify that the child process really exits,
         * just move on with the restart.
         */
        CloseHandle(event_handles[CHILD_HANDLE]);
        event_handles[CHILD_HANDLE] = NULL;
    }
    else {
        /* The child process exited prematurely due to a fatal error. */
        DWORD exitcode;
        if (!GetExitCodeProcess(event_handles[CHILD_HANDLE], &exitcode)) {
            /* HUH? We did exit, didn't we? */
            exitcode = APEXIT_CHILDFATAL;
        }
        if (   exitcode == APEXIT_CHILDFATAL
            || exitcode == APEXIT_CHILDINIT
            || exitcode == APEXIT_INIT) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(00427)
                         "Parent: child process %lu exited with status %lu -- Aborting.",
                         child_pid, exitcode);
            shutdown_pending = 1;
        }
        else {
            int i;
            restart_pending = 1;
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00428)
                         "Parent: child process %lu exited with status %lu -- Restarting.",
                         child_pid, exitcode);
            for (i = 0; i < ap_threads_per_child; i++) {
                ap_update_child_status_from_indexes(0, i, SERVER_DEAD, NULL);
            }
        }
        CloseHandle(event_handles[CHILD_HANDLE]);
        event_handles[CHILD_HANDLE] = NULL;
    }

    winnt_note_child_killed(/* slot */ 0);

    if (restart_pending) {
        ++my_generation;
        ap_scoreboard_image->global->running_generation = my_generation;
    }
die_now:
    if (shutdown_pending)
    {
        int timeout = 30000;  /* Timeout is milliseconds */
        winnt_mpm_state = AP_MPMQ_STOPPING;

        if (!child_created) {
            return 0;  /* Tell the caller we do not want to restart */
        }

        /* This shutdown is only marginally graceful. We will give the
         * child a bit of time to exit gracefully. If the time expires,
         * the child will be wacked.
         */
        if (!strcasecmp(signal_arg, "runservice")) {
            mpm_service_stopping();
        }
        /* Signal the child processes to exit */
        if (SetEvent(child_exit_event) == 0) {
                ap_log_error(APLOG_MARK,APLOG_ERR, apr_get_os_error(), ap_server_conf, APLOGNO(00429)
                             "Parent: SetEvent for child process event %pp failed",
                             event_handles[CHILD_HANDLE]);
        }
        if (event_handles[CHILD_HANDLE]) {
            rv = WaitForSingleObject(event_handles[CHILD_HANDLE], timeout);
            if (rv == WAIT_OBJECT_0) {
                ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00430)
                             "Parent: Child process %lu exited successfully.", child_pid);
                CloseHandle(event_handles[CHILD_HANDLE]);
                event_handles[CHILD_HANDLE] = NULL;
            }
            else {
                ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00431)
                             "Parent: Forcing termination of child process %lu",
                             child_pid);
                TerminateProcess(event_handles[CHILD_HANDLE], 1);
                CloseHandle(event_handles[CHILD_HANDLE]);
                event_handles[CHILD_HANDLE] = NULL;
            }
        }
        CloseHandle(child_exit_event);
        return 0;  /* Tell the caller we do not want to restart */
    }
    winnt_mpm_state = AP_MPMQ_STARTING;
    CloseHandle(child_exit_event);
    return 1;      /* Tell the caller we want a restart */
}

/* service_nt_main_fn needs to append the StartService() args
 * outside of our call stack and thread as the service starts...
 */
apr_array_header_t *mpm_new_argv;

/* Remember service_to_start failures to log and fail in pre_config.
 * Remember inst_argc and inst_argv for installing or starting the
 * service after we preflight the config.
 */

static int winnt_query(int query_code, int *result, apr_status_t *rv)
{
    *rv = APR_SUCCESS;
    switch (query_code) {
        case AP_MPMQ_MAX_DAEMON_USED:
            *result = MAXIMUM_WAIT_OBJECTS;
            break;
        case AP_MPMQ_IS_THREADED:
            *result = AP_MPMQ_STATIC;
            break;
        case AP_MPMQ_IS_FORKED:
            *result = AP_MPMQ_NOT_SUPPORTED;
            break;
        case AP_MPMQ_HARD_LIMIT_DAEMONS:
            *result = HARD_SERVER_LIMIT;
            break;
        case AP_MPMQ_HARD_LIMIT_THREADS:
            *result = thread_limit;
            break;
        case AP_MPMQ_MAX_THREADS:
            *result = ap_threads_per_child;
            break;
        case AP_MPMQ_MIN_SPARE_DAEMONS:
            *result = 0;
            break;
        case AP_MPMQ_MIN_SPARE_THREADS:
            *result = 0;
            break;
        case AP_MPMQ_MAX_SPARE_DAEMONS:
            *result = 0;
            break;
        case AP_MPMQ_MAX_SPARE_THREADS:
            *result = 0;
            break;
        case AP_MPMQ_MAX_REQUESTS_DAEMON:
            *result = ap_max_requests_per_child;
            break;
        case AP_MPMQ_MAX_DAEMONS:
            *result = 1;
            break;
        case AP_MPMQ_MPM_STATE:
            *result = winnt_mpm_state;
            break;
        case AP_MPMQ_GENERATION:
            *result = my_generation;
            break;
        default:
            *rv = APR_ENOTIMPL;
            break;
    }
    return OK;
}

static const char *winnt_get_name(void)
{
    return "WinNT";
}

#define SERVICE_UNSET (-1)
static apr_status_t service_set = SERVICE_UNSET;
static apr_status_t service_to_start_success;
static int inst_argc;
static const char * const *inst_argv;
static const char *service_name = NULL;

static void winnt_rewrite_args(process_rec *process)
{
    /* Handle the following SCM aspects in this phase:
     *
     *   -k runservice [transition in service context only]
     *   -k install
     *   -k config
     *   -k uninstall
     *   -k stop
     *   -k shutdown (same as -k stop). Maintained for backward compatibility.
     *
     * We can't leave this phase until we know our identity
     * and modify the command arguments appropriately.
     *
     * We do not care if the .conf file exists or is parsable when
     * attempting to stop or uninstall a service.
     */
    apr_status_t rv;
    char *def_server_root;
    char *binpath;
    char optbuf[3];
    const char *opt_arg;
    int fixed_args;
    char *pid;
    apr_getopt_t *opt;
    int running_as_service = 1;
    int errout = 0;
    apr_file_t *nullfile;

    pconf = process->pconf;

    osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osver);

    /* We wish this was *always* a reservation, but sadly it wasn't so and
     * we couldn't break a hard limit prior to NT Kernel 5.1
     */
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT
        && ((osver.dwMajorVersion > 5)
         || ((osver.dwMajorVersion == 5) && (osver.dwMinorVersion > 0)))) {
        stack_res_flag = STACK_SIZE_PARAM_IS_A_RESERVATION;
    }

    /* AP_PARENT_PID is only valid in the child */
    pid = getenv("AP_PARENT_PID");
    if (pid)
    {
        HANDLE filehand;
        HANDLE hproc = GetCurrentProcess();
        DWORD BytesRead;

        /* This is the child */
        my_pid = GetCurrentProcessId();
        parent_pid = (DWORD) atol(pid);

        /* Prevent holding open the (nonexistent) console */
        ap_real_exit_code = 0;

        /* The parent gave us stdin, we need to remember this
         * handle, and no longer inherit it at our children
         * (we can't slurp it up now, we just aren't ready yet).
         * The original handle is closed below, at apr_file_dup2()
         */
        pipe = GetStdHandle(STD_INPUT_HANDLE);
        if (DuplicateHandle(hproc, pipe,
                            hproc, &filehand, 0, FALSE,
                            DUPLICATE_SAME_ACCESS)) {
            pipe = filehand;
        }

        /* The parent gave us stdout of the NUL device,
         * and expects us to suck up stdin of all of our
         * shared handles and data from the parent.
         * Don't infect child processes with our stdin
         * handle, use another handle to NUL!
         */
        {
            apr_file_t *infile, *outfile;
            if ((apr_file_open_stdout(&outfile, process->pool) == APR_SUCCESS)
             && (apr_file_open_stdin(&infile, process->pool) == APR_SUCCESS))
                apr_file_dup2(infile, outfile, process->pool);
        }

        /* This child needs the existing stderr opened for logging,
         * already
         */

        /* Read this child's generation number as soon as now,
         * so that further hooks can query it.
         */
        if (!ReadFile(pipe, &my_generation, sizeof(my_generation),
                      &BytesRead, (LPOVERLAPPED) NULL)
                || (BytesRead != sizeof(my_generation))) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), NULL, APLOGNO(02965)
                         "Child: Unable to retrieve my generation from the parent");
            exit(APEXIT_CHILDINIT);
        }

        /* The parent is responsible for providing the
         * COMPLETE ARGUMENTS REQUIRED to the child.
         *
         * No further argument parsing is needed, but
         * for good measure we will provide a simple
         * signal string for later testing.
         */
        signal_arg = "runchild";
        return;
    }

    /* This is the parent, we have a long way to go :-) */
    parent_pid = my_pid = GetCurrentProcessId();

    /* This behavior is voided by setting real_exit_code to 0 */
    atexit(hold_console_open_on_error);

    /* Rewrite process->argv[];
     *
     * strip out -k signal into signal_arg
     * strip out -n servicename and set the names
     * add default -d serverroot from the path of this executable
     *
     * The end result will look like:
     *
     * The invocation command (%0)
     *     The -d serverroot default from the running executable
     *         The requested service's (-n) registry ConfigArgs
     *             The WinNT SCM's StartService() args
     */
    if ((rv = ap_os_proc_filepath(&binpath, process->pconf))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_CRIT, rv, NULL, APLOGNO(00432)
                     "Failed to get the full path of %s", process->argv[0]);
        exit(APEXIT_INIT);
    }
    /* WARNING: There is an implict assumption here that the
     * executable resides in ServerRoot or ServerRoot\bin
     */
    def_server_root = (char *) apr_filepath_name_get(binpath);
    if (def_server_root > binpath) {
        *(def_server_root - 1) = '\0';
        def_server_root = (char *) apr_filepath_name_get(binpath);
        if (!strcasecmp(def_server_root, "bin"))
            *(def_server_root - 1) = '\0';
    }
    apr_filepath_merge(&def_server_root, NULL, binpath,
                       APR_FILEPATH_TRUENAME, process->pool);

    /* Use process->pool so that the rewritten argv
     * lasts for the lifetime of the server process,
     * because pconf will be destroyed after the
     * initial pre-flight of the config parser.
     */
    mpm_new_argv = apr_array_make(process->pool, process->argc + 2,
                                  sizeof(const char *));
    *(const char **)apr_array_push(mpm_new_argv) = process->argv[0];
    *(const char **)apr_array_push(mpm_new_argv) = "-d";
    *(const char **)apr_array_push(mpm_new_argv) = def_server_root;

    fixed_args = mpm_new_argv->nelts;

    optbuf[0] = '-';
    optbuf[2] = '\0';
    apr_getopt_init(&opt, process->pool, process->argc, process->argv);
    opt->errfn = NULL;
    while ((rv = apr_getopt(opt, "wn:k:" AP_SERVER_BASEARGS,
                            optbuf + 1, &opt_arg)) == APR_SUCCESS) {
        switch (optbuf[1]) {

        /* Shortcuts; include the -w option to hold the window open on error.
         * This must not be toggled once we reset ap_real_exit_code to 0!
         */
        case 'w':
            if (ap_real_exit_code)
                ap_real_exit_code = 2;
            break;

        case 'n':
            service_set = mpm_service_set_name(process->pool, &service_name,
                                               opt_arg);
            break;

        case 'k':
            signal_arg = opt_arg;
            break;

        case 'E':
            errout = 1;
            /* Fall through so the Apache main() handles the 'E' arg */
        default:
            *(const char **)apr_array_push(mpm_new_argv) =
                apr_pstrdup(process->pool, optbuf);

            if (opt_arg) {
                *(const char **)apr_array_push(mpm_new_argv) = opt_arg;
            }
            break;
        }
    }

    /* back up to capture the bad argument */
    if (rv == APR_BADCH || rv == APR_BADARG) {
        opt->ind--;
    }

    while (opt->ind < opt->argc) {
        *(const char **)apr_array_push(mpm_new_argv) =
            apr_pstrdup(process->pool, opt->argv[opt->ind++]);
    }

    /* Track the number of args actually entered by the user */
    inst_argc = mpm_new_argv->nelts - fixed_args;

    /* Provide a default 'run' -k arg to simplify signal_arg tests */
    if (!signal_arg)
    {
        signal_arg = "run";
        running_as_service = 0;
    }

    if (!strcasecmp(signal_arg, "runservice"))
    {
        /* Start the NT Service _NOW_ because the WinNT SCM is
         * expecting us to rapidly assume control of our own
         * process, the SCM will tell us our service name, and
         * may have extra StartService() command arguments to
         * add for us.
         *
         * The SCM will generally invoke the executable with
         * the c:\win\system32 default directory.  This is very
         * lethal if folks use ServerRoot /foopath on windows
         * without a drive letter.  Change to the default root
         * (path to apache root, above /bin) for safety.
         */
        apr_filepath_set(def_server_root, process->pool);

        /* Any other process has a console, so we don't to begin
         * a Win9x service until the configuration is parsed and
         * any command line errors are reported.
         *
         * We hold the return value so that we can die in pre_config
         * after logging begins, and the failure can land in the log.
         */
        if (!errout) {
            mpm_nt_eventlog_stderr_open(service_name, process->pool);
        }
        service_to_start_success = mpm_service_to_start(&service_name,
                                                        process->pool);
        if (service_to_start_success == APR_SUCCESS) {
            service_set = APR_SUCCESS;
        }

        /* Open a null handle to soak stdout in this process.
         * Windows service processes are missing any file handle
         * usable for stdin/out/err.  This was the cause of later
         * trouble with invocations of apr_file_open_stdout()
         */
        if ((rv = apr_file_open(&nullfile, "NUL",
                                APR_READ | APR_WRITE, APR_OS_DEFAULT,
                                process->pool)) == APR_SUCCESS) {
            apr_file_t *nullstdout;
            if (apr_file_open_stdout(&nullstdout, process->pool)
                    == APR_SUCCESS)
                apr_file_dup2(nullstdout, nullfile, process->pool);
            apr_file_close(nullfile);
        }
    }

    /* Get the default for any -k option, except run */
    if (service_set == SERVICE_UNSET && strcasecmp(signal_arg, "run")) {
        service_set = mpm_service_set_name(process->pool, &service_name,
                                           AP_DEFAULT_SERVICE_NAME);
    }

    if (!strcasecmp(signal_arg, "install")) /* -k install */
    {
        if (service_set == APR_SUCCESS)
        {
            ap_log_error(APLOG_MARK,APLOG_ERR, 0, NULL, APLOGNO(00433)
                 "%s: Service is already installed.", service_name);
            exit(APEXIT_INIT);
        }
    }
    else if (running_as_service)
    {
        if (service_set == APR_SUCCESS)
        {
            /* Attempt to Uninstall, or stop, before
             * we can read the arguments or .conf files
             */
            if (!strcasecmp(signal_arg, "uninstall")) {
                rv = mpm_service_uninstall();
                exit(rv);
            }

            if ((!strcasecmp(signal_arg, "stop")) ||
                (!strcasecmp(signal_arg, "shutdown"))) {
                mpm_signal_service(process->pool, 0);
                exit(0);
            }

            rv = mpm_merge_service_args(process->pool, mpm_new_argv,
                                        fixed_args);
            if (rv == APR_SUCCESS) {
                ap_log_error(APLOG_MARK,APLOG_INFO, 0, NULL, APLOGNO(00434)
                             "Using ConfigArgs of the installed service "
                             "\"%s\".", service_name);
            }
            else  {
                ap_log_error(APLOG_MARK,APLOG_WARNING, rv, NULL, APLOGNO(00435)
                             "No installed ConfigArgs for the service "
                             "\"%s\", using Apache defaults.", service_name);
            }
        }
        else
        {
            ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL, APLOGNO(00436)
                 "No installed service named \"%s\".", service_name);
            exit(APEXIT_INIT);
        }
    }
    if (strcasecmp(signal_arg, "install") && service_set && service_set != SERVICE_UNSET)
    {
        ap_log_error(APLOG_MARK,APLOG_ERR, service_set, NULL, APLOGNO(00437)
             "No installed service named \"%s\".", service_name);
        exit(APEXIT_INIT);
    }

    /* Track the args actually entered by the user.
     * These will be used for the -k install parameters, as well as
     * for the -k start service override arguments.
     */
    inst_argv = (const char * const *)mpm_new_argv->elts
        + mpm_new_argv->nelts - inst_argc;

    /* Now, do service install or reconfigure then proceed to
     * post_config to test the installed configuration.
     */
    if (!strcasecmp(signal_arg, "config")) { /* -k config */
        /* Reconfigure the service */
        rv = mpm_service_install(process->pool, inst_argc, inst_argv, 1);
        if (rv != APR_SUCCESS) {
            exit(rv);
        }

        fprintf(stderr,"Testing httpd.conf....\n");
        fprintf(stderr,"Errors reported here must be corrected before the "
                "service can be started.\n");
    }
    else if (!strcasecmp(signal_arg, "install")) { /* -k install */
        /* Install the service */
        rv = mpm_service_install(process->pool, inst_argc, inst_argv, 0);
        if (rv != APR_SUCCESS) {
            exit(rv);
        }

        fprintf(stderr,"Testing httpd.conf....\n");
        fprintf(stderr,"Errors reported here must be corrected before the "
                "service can be started.\n");
    }

    process->argc = mpm_new_argv->nelts;
    process->argv = (const char * const *) mpm_new_argv->elts;
}


static int winnt_pre_config(apr_pool_t *pconf_, apr_pool_t *plog, apr_pool_t *ptemp)
{
    /* Handle the following SCM aspects in this phase:
     *
     *   -k runservice [WinNT errors logged from rewrite_args]
     */

    /* Initialize shared static objects.
     * TODO: Put config related statics into an sconf structure.
     */
    pconf = pconf_;

    if (ap_exists_config_define("ONE_PROCESS") ||
        ap_exists_config_define("DEBUG"))
        one_process = -1;

    /* XXX: presume proper privilages; one nice thing would be
     * a loud emit if running as "LocalSystem"/"SYSTEM" to indicate
     * they should change to a user with write access to logs/ alone.
     */
    ap_sys_privileges_handlers(1);

    if (!strcasecmp(signal_arg, "runservice")
            && (service_to_start_success != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK,APLOG_CRIT, service_to_start_success, NULL, APLOGNO(00438)
                     "%s: Unable to start the service manager.",
                     service_name);
        exit(APEXIT_INIT);
    }
    else if (ap_state_query(AP_SQ_RUN_MODE) == AP_SQ_RM_NORMAL
             && !one_process && !my_generation) {
        /* Open a null handle to soak stdout in this process.
         * We need to emulate apr_proc_detach, unix performs this
         * same check in the pre_config hook (although it is
         * arguably premature).  Services already fixed this.
         */
        apr_file_t *nullfile;
        apr_status_t rv;
        apr_pool_t *pproc = apr_pool_parent_get(pconf);

        if ((rv = apr_file_open(&nullfile, "NUL",
                                APR_READ | APR_WRITE, APR_OS_DEFAULT,
                                pproc)) == APR_SUCCESS) {
            apr_file_t *nullstdout;
            if (apr_file_open_stdout(&nullstdout, pproc)
                    == APR_SUCCESS)
                apr_file_dup2(nullstdout, nullfile, pproc);
            apr_file_close(nullfile);
        }
    }

    ap_listen_pre_config();
    thread_limit = DEFAULT_THREAD_LIMIT;
    ap_threads_per_child = DEFAULT_THREADS_PER_CHILD;

    return OK;
}

static int winnt_check_config(apr_pool_t *pconf, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec* s)
{
    int is_parent;
    int startup = 0;

    /* We want this only in the parent and only the first time around */
    is_parent = (parent_pid == my_pid);
    if (is_parent &&
        ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        startup = 1;
    }

    if (thread_limit > MAX_THREAD_LIMIT) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00439)
                         "WARNING: ThreadLimit of %d exceeds compile-time "
                         "limit of %d threads, decreasing to %d.",
                         thread_limit, MAX_THREAD_LIMIT, MAX_THREAD_LIMIT);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00440)
                         "ThreadLimit of %d exceeds compile-time limit "
                         "of %d, decreasing to match",
                         thread_limit, MAX_THREAD_LIMIT);
        }
        thread_limit = MAX_THREAD_LIMIT;
    }
    else if (thread_limit < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00441)
                         "WARNING: ThreadLimit of %d not allowed, "
                         "increasing to 1.", thread_limit);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00442)
                         "ThreadLimit of %d not allowed, increasing to 1",
                         thread_limit);
        }
        thread_limit = 1;
    }

    /* You cannot change ThreadLimit across a restart; ignore
     * any such attempts.
     */
    if (!first_thread_limit) {
        first_thread_limit = thread_limit;
    }
    else if (thread_limit != first_thread_limit) {
        /* Don't need a startup console version here */
        if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00443)
                         "changing ThreadLimit to %d from original value "
                         "of %d not allowed during restart",
                         thread_limit, first_thread_limit);
        }
        thread_limit = first_thread_limit;
    }

    if (ap_threads_per_child > thread_limit) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00444)
                         "WARNING: ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d threads, decreasing to %d. To increase, please "
                         "see the ThreadLimit directive.",
                         ap_threads_per_child, thread_limit, thread_limit);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00445)
                         "ThreadsPerChild of %d exceeds ThreadLimit "
                         "of %d, decreasing to match",
                         ap_threads_per_child, thread_limit);
        }
        ap_threads_per_child = thread_limit;
    }
    else if (ap_threads_per_child < 1) {
        if (startup) {
            ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_STARTUP, 0, NULL, APLOGNO(00446)
                         "WARNING: ThreadsPerChild of %d not allowed, "
                         "increasing to 1.", ap_threads_per_child);
        } else if (is_parent) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(00447)
                         "ThreadsPerChild of %d not allowed, increasing to 1",
                         ap_threads_per_child);
        }
        ap_threads_per_child = 1;
    }

    return OK;
}

static int winnt_post_config(apr_pool_t *pconf, apr_pool_t *plog, apr_pool_t *ptemp, server_rec* s)
{
    apr_status_t rv = 0;

    /* Handle the following SCM aspects in this phase:
     *
     *   -k install (catch and exit as install was handled in rewrite_args)
     *   -k config  (catch and exit as config was handled in rewrite_args)
     *   -k start
     *   -k restart
     *   -k runservice [Win95, only once - after we parsed the config]
     *
     * because all of these signals are useful _only_ if there
     * is a valid conf\httpd.conf environment to start.
     *
     * We reached this phase by avoiding errors that would cause
     * these options to fail unexpectedly in another process.
     */

    if (!strcasecmp(signal_arg, "install")) {
        /* Service install happens in the rewrite_args hooks. If we
         * made it this far, the server configuration is clean and the
         * service will successfully start.
         */
        apr_pool_destroy(s->process->pool);
        apr_terminate();
        exit(0);
    }
    if (!strcasecmp(signal_arg, "config")) {
        /* Service reconfiguration happens in the rewrite_args hooks. If we
         * made it this far, the server configuration is clean and the
         * service will successfully start.
         */
        apr_pool_destroy(s->process->pool);
        apr_terminate();
        exit(0);
    }

    if (!strcasecmp(signal_arg, "start")) {
        ap_listen_rec *lr;

        /* Close the listening sockets. */
        for (lr = ap_listeners; lr; lr = lr->next) {
            apr_socket_close(lr->sd);
            lr->active = 0;
        }
        rv = mpm_service_start(ptemp, inst_argc, inst_argv);
        apr_pool_destroy(s->process->pool);
        apr_terminate();
        exit (rv);
    }

    if (!strcasecmp(signal_arg, "restart")) {
        mpm_signal_service(ptemp, 1);
        apr_pool_destroy(s->process->pool);
        apr_terminate();
        exit (rv);
    }

    if (parent_pid == my_pid)
    {
        if (ap_state_query(AP_SQ_MAIN_STATE) != AP_SQ_MS_CREATE_PRE_CONFIG
            && ap_state_query(AP_SQ_CONFIG_GEN) == 1)
        {
            /* This code should be run once in the parent and not run
             * across a restart
             */
            PSECURITY_ATTRIBUTES sa = GetNullACL();  /* returns NULL if invalid (Win95?) */
            setup_signal_names(apr_psprintf(pconf, "ap%lu", parent_pid));

            ap_log_pid(pconf, ap_pid_fname);

            /* Create shutdown event, apPID_shutdown, where PID is the parent
             * Apache process ID. Shutdown is signaled by 'apache -k shutdown'.
             */
            shutdown_event = CreateEvent(sa, FALSE, FALSE, signal_shutdown_name);
            if (!shutdown_event) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00448)
                             "Parent: Cannot create shutdown event %s", signal_shutdown_name);
                CleanNullACL((void *)sa);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            /* Create restart event, apPID_restart, where PID is the parent
             * Apache process ID. Restart is signaled by 'apache -k restart'.
             */
            restart_event = CreateEvent(sa, FALSE, FALSE, signal_restart_name);
            if (!restart_event) {
                CloseHandle(shutdown_event);
                ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), ap_server_conf, APLOGNO(00449)
                             "Parent: Cannot create restart event %s", signal_restart_name);
                CleanNullACL((void *)sa);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            CleanNullACL((void *)sa);

            /* Create the start mutex, as an unnamed object for security.
             * Ths start mutex is used during a restart to prevent more than
             * one child process from entering the accept loop at once.
             */
            rv =  apr_proc_mutex_create(&start_mutex, NULL,
                                        APR_LOCK_DEFAULT,
                                        ap_server_conf->process->pool);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf, APLOGNO(00450)
                             "%s: Unable to create the start_mutex.",
                             service_name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        /* Always reset our console handler to be the first, even on a restart
        *  because some modules (e.g. mod_perl) might have set a console
        *  handler to terminate the process.
        */
        if (strcasecmp(signal_arg, "runservice"))
            mpm_start_console_handler();
    }
    else /* parent_pid != my_pid */
    {
        mpm_start_child_console_handler();
    }
    return OK;
}

/* This really should be a post_config hook, but the error log is already
 * redirected by that point, so we need to do this in the open_logs phase.
 */
static int winnt_open_logs(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    /* Initialize shared static objects.
     */
    if (parent_pid != my_pid) {
        return OK;
    }

    /* We cannot initialize our listeners if we are restarting
     * (the parent process already has glomed on to them)
     * nor should we do so for service reconfiguration
     * (since the service may already be running.)
     */
    if (!strcasecmp(signal_arg, "restart")
            || !strcasecmp(signal_arg, "config")) {
        return OK;
    }

    if (ap_setup_listeners(s) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0,
                     NULL, APLOGNO(00451) "no listening sockets available, shutting down");
        return !OK;
    }

    return OK;
}

static void winnt_child_init(apr_pool_t *pchild, struct server_rec *s)
{
    apr_status_t rv;

    setup_signal_names(apr_psprintf(pchild, "ap%lu", parent_pid));

    /* This is a child process, not in single process mode */
    if (!one_process) {
        /* Set up events and the scoreboard */
        get_handles_from_parent(s, &exit_event, &start_mutex,
                                &ap_scoreboard_shm);

        /* Set up the listeners */
        get_listeners_from_parent(s);

        /* Done reading from the parent, close that channel */
        CloseHandle(pipe);
    }
    else {
        /* Single process mode - this lock doesn't even need to exist */
        rv = apr_proc_mutex_create(&start_mutex, signal_name_prefix,
                                   APR_LOCK_DEFAULT, s->process->pool);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf, APLOGNO(00452)
                         "%s child: Unable to init the start_mutex.",
                         service_name);
            exit(APEXIT_CHILDINIT);
        }

        /* Borrow the shutdown_even as our _child_ loop exit event */
        exit_event = shutdown_event;
    }
}


static int winnt_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s )
{
    static int restart = 0;            /* Default is "not a restart" */

    /* ### If non-graceful restarts are ever introduced - we need to rerun
     * the pre_mpm hook on subsequent non-graceful restarts.  But Win32
     * has only graceful style restarts - and we need this hook to act
     * the same on Win32 as on Unix.
     */
    if (!restart && ((parent_pid == my_pid) || one_process)) {
        /* Set up the scoreboard. */
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            return !OK;
        }
    }

    if ((parent_pid != my_pid) || one_process)
    {
        /* The child process or in one_process (debug) mode
         */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00453)
                     "Child process is running");

        child_main(pconf, parent_pid);

        ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00454)
                     "Child process is exiting");
        return DONE;
    }
    else
    {
        /* A real-honest to goodness parent */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00455)
                     "%s configured -- resuming normal operations",
                     ap_get_server_description());
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00456)
                     "Server built: %s", ap_get_server_built());
        ap_log_command_line(plog, s);
        ap_log_mpm_common(s);

        restart = master_main(ap_server_conf, shutdown_event, restart_event);

        if (!restart)
        {
            /* Shutting down. Clean up... */
            ap_remove_pid(pconf, ap_pid_fname);
            apr_proc_mutex_destroy(start_mutex);

            CloseHandle(restart_event);
            CloseHandle(shutdown_event);

            return DONE;
        }
    }

    return OK; /* Restart */
}

static void winnt_hooks(apr_pool_t *p)
{
    /* Our open_logs hook function must run before the core's, or stderr
     * will be redirected to a file, and the messages won't print to the
     * console.
     */
    static const char *const aszSucc[] = {"core.c", NULL};

    ap_hook_pre_config(winnt_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_check_config(winnt_check_config, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_post_config(winnt_post_config, NULL, NULL, 0);
    ap_hook_child_init(winnt_child_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_open_logs(winnt_open_logs, NULL, aszSucc, APR_HOOK_REALLY_FIRST);
    ap_hook_mpm(winnt_run, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm_query(winnt_query, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_mpm_get_name(winnt_get_name, NULL, NULL, APR_HOOK_MIDDLE);
}

AP_DECLARE_MODULE(mpm_winnt) = {
    MPM20_MODULE_STUFF,
    winnt_rewrite_args,    /* hook to run before apache parses args */
    NULL,                  /* create per-directory config structure */
    NULL,                  /* merge per-directory config structures */
    NULL,                  /* create per-server config structure */
    NULL,                  /* merge per-server config structures */
    winnt_cmds,            /* command apr_table_t */
    winnt_hooks            /* register_hooks */
};

#endif /* def WIN32 */
