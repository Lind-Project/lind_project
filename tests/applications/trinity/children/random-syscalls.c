/*
 * Call a single random syscall with random args.
 */

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arch.h"	// biarch
#include "child.h"
#include "debug.h"
#include "locks.h"
#include "log.h"
#include "pids.h"
#include "random.h"
#include "shm.h"
#include "signals.h"
#include "sanitise.h"
#include "syscall.h"
#include "tables.h"
#include "trinity.h"

/*
 * This function decides if we're going to be doing a 32bit or 64bit syscall.
 * There are various factors involved here, from whether we're on a 32-bit only arch
 * to 'we asked to do a 32bit only syscall' and more.. Hairy.
 */

static int *active_syscalls;

static bool choose_syscall_table(void)
{
	bool do32 = FALSE;

	if (biarch == FALSE) {
		active_syscalls = shm->active_syscalls;
	} else {

		/* First, check that we have syscalls enabled in either table. */
		if (validate_syscall_table_64() == FALSE) {
			use_64bit = FALSE;
			/* If no 64bit syscalls enabled, force 32bit. */
			do32 = TRUE;
		}

		if (validate_syscall_table_32() == FALSE)
			use_32bit = FALSE;

		/* If both tables enabled, pick randomly. */
		if ((use_64bit == TRUE) && (use_32bit == TRUE)) {
			/* 10% possibility of a 32bit syscall */
			if (ONE_IN(10))
				do32 = TRUE;
		}

		if (do32 == FALSE) {
			syscalls = syscalls_64bit;
			active_syscalls = shm->active_syscalls64;
			max_nr_syscalls = max_nr_64bit_syscalls;
		} else {
			syscalls = syscalls_32bit;
			active_syscalls = shm->active_syscalls32;
			max_nr_syscalls = max_nr_32bit_syscalls;
		}
	}
	return do32;
}

bool child_random_syscalls(void)
{
	struct syscallrecord *rec;
	unsigned int syscallnr;
	bool do32;
	unsigned int len;
	unsigned long a1, a2, a3;
	time_t old;
	pid_t oldpid;

retry:
	if (no_syscalls_enabled() == TRUE) {
		output(0, "[%d] No more syscalls enabled. Exiting\n", getpid());
		shm->exit_reason = EXIT_NO_SYSCALLS_ENABLED;
		return FAIL;
	}

	/* Ok, we're doing another syscall, let's pick one. */
	do32 = choose_syscall_table();
	syscallnr = rand() % max_nr_syscalls;

	/* If we got a syscallnr which is not active repeat the attempt,
	 * since another child has switched that syscall off already.*/
	if (active_syscalls[syscallnr] == 0)
		goto retry;

	syscallnr = active_syscalls[syscallnr] - 1;

	if (validate_specific_syscall_silent(syscalls, syscallnr) == FALSE) {
		deactivate_syscall(syscallnr, do32);
		goto retry;
	}

	rec = &this_child->syscall;
	/* critical section for shm updates. */
	lock(&rec->lock);
	rec->do32bit = do32;
	rec->nr = syscallnr;
	unlock(&rec->lock);

	if (syscalls_todo) {
		if (shm->stats.total_syscalls_done >= syscalls_todo)
			shm->exit_reason = EXIT_REACHED_COUNT;
	}

	/* Generate arguments, print them out */

	generate_syscall_args(rec);

	a1 = rec->a1;
	a2 = rec->a2;
	a3 = rec->a3;
	oldpid = this_child->pid;

	output_syscall_prefix(rec);

	/* Sanity check: Make sure the length of the buffer remains
	 * constant across the syscall.
	 */
	len = strlen(rec->prebuffer);

	old = rec->tv.tv_sec;
	do_syscall(rec);

	if (this_child->pid == 0) {
		output(0, "Sanity check failed. my pid became zero after syscall:%s(%lx, %lx, %lx)  was:%d\n",
				print_syscall_name(syscallnr, do32),
				a1, a2, a3, oldpid);
			dump_childnos();
			dump_childdata(this_child);
			panic(EXIT_PID_OUT_OF_RANGE);
	}

	if (old != 0) {
		// FIXME: Should factor in loadavg here, as with enough pids, a child can exceed 60s
		//  without getting scheduled.
		if (rec->tv.tv_sec - old > 60) {
			output(0, "Sanity check failed. Something stomped on rec->tv after syscall:%s(%lx, %lx, %lx)  was:%lx now:%lx.\n",
				print_syscall_name(syscallnr, do32),
				a1, a2, a3, old, rec->tv.tv_sec);
			dump_childnos();
			dump_childdata(this_child);
			panic(EXIT_PID_OUT_OF_RANGE);
		}
	}

	/* post syscall sanity checks. */
	if (len != strlen(rec->prebuffer)) {
		output(0, "Sanity check failed: prebuffer length changed from %d to %d after syscall:%s(%lx, %lx, %lx).\n",
			len, strlen(rec->prebuffer),
			print_syscall_name(syscallnr, do32),
			a1, a2, a3);
		dump_childnos();
		dump_childdata(this_child);
		panic(EXIT_PID_OUT_OF_RANGE);
	}

	/* Output the syscall result, and clean up */
	output_syscall_postfix(rec);

	handle_syscall_ret(rec);

	return TRUE;
}
