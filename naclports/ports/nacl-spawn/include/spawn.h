/*
 * Copyright (c) 2014 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <setjmp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include_next <spawn.h>

/*
 * Include guards are here so that this header can forward to the next one in
 * presence of an already installed copy of nacl-spawn.
 */
#ifndef NACL_SPAWN_SPAWN_H_
#define NACL_SPAWN_SPAWN_H_

__BEGIN_DECLS

/*
 * Spawn a child using the given args.
 *
 * Args:
 *   mode: Execute mode, one of the defines below.
 *   path: The program to run.
 *   argv: The startup arguments for the child.
 * Returns:
 *   Process id of the child or -1 for error.
 */
int spawnv(int mode, const char* path, char *const argv[]);

/*
 * Spawn a child using the current environment and given args.
 *
 * Args:
 *   mode: Execute mode, one of the defines below.
 *   path: The program to run.
 *   argv: The startup arguments for the child.
 *   envp: The environment to run the child in.
 * Returns:
 *   Process id of the child or -1 for error.
 */
int spawnve(int mode, const char* path, char *const argv[], char *const envp[]);
#define P_WAIT 0
#define P_NOWAIT 1
#define P_NOWAITO 1
#define P_OVERLAY 2

/*
 * Synchronously eval JavaScript.
 *
 * Args:
 *   cmd: Null terminated string containing code to eval.
 *   data: Pointer to a char* to receive eval string result.
 *   len: Pointer to a size_t to receive the length of the result.
 */
void jseval(const char* cmd, char** data, size_t* len);

/*
 * Create a pipe that can communicate cross-process via JS.
 *
 * Args:
 *   pipefd: Point to place to store a read [0] and write [1] fd.
 * Returns:
 *   Zero on success.
 * TODO(bradnelson): The should work differently, see both:
 * https://bugs.chromium.org/p/webports/issues/detail?id=247
 * https://bugs.chromium.org/p/webports/issues/detail?id=248
 * Only declared when pipe is not defined as doing -Dpipe=nacl_spawn_pipe
 * is a common (though not universal) way to inject this.
 * In this case, system headers declaration of pipe don't always match
 * this definition of pipe.
 */
#if !defined(pipe)
int nacl_spawn_pipe(int pipefd[2]);
#endif

/*
 * Create a pipe that can communicate cross-process via JS w/ flags.
 *
 * Args:
 *   pipefd: Point to place to store a read [0] and write [1] fd.
 *   flags: Flags to create the fd's with (for example O_NONBLOCK).
 * Returns:
 *   Zero on success.
 * TODO(bradnelson): The should work differently, see both:
 * https://bugs.chromium.org/p/webports/issues/detail?id=247
 * https://bugs.chromium.org/p/webports/issues/detail?id=248
 */
int nacl_spawn_pipe2(int pipefd[2], int flags);

/*
 * Implement vfork as a macro.
 *
 * Returns:
 *   Pid of a child, or zero if in the child.
 *
 * Done as a macro in order to allow portable implementation of
 * vfork's behavior, which requires multiple returns from the same
 * code location.
 * A before function is called to setup vfork state,
 * followed by setjmp passing its result to an after function.
 * A global setjmp buffer is used.
 */
void nacl_spawn_vfork_before(void);
pid_t nacl_spawn_vfork_after(int jmping);

extern __thread jmp_buf nacl_spawn_vfork_env;
#define vfork() (nacl_spawn_vfork_before(), \
    nacl_spawn_vfork_after(setjmp(nacl_spawn_vfork_env)))

/*
 * Exit immediately with no cleanup.
 *
 * Args:
 *   status: Exit status to return from process.
 *
 * Implemented as a macro to ensure we get the nacl_spawn version hooked
 * to interoperate with vfork in the case of an error.
 */
void nacl_spawn_vfork_exit(int status);
#if !defined(IN_NACL_SPAWN_CC)
#define _exit(status) nacl_spawn_vfork_exit(status)
#endif

/*
 * Declarations of exec variants we support that aren't in our libc headers.
 *
 * The newer version of glibc already declared execvpe
 */
#if !defined(__GLIBC__) ||  (__GLIBC__ == 2 && __GLIBC_MINOR__ == 9)
int execvpe(const char *file, char *const argv[], char *const envp[]);
#endif
int execlpe(const char *path, const char *arg, ...); /* char* const envp[] */

__END_DECLS

#endif /* NACL_SPAWN_SPAWN_H_ */
