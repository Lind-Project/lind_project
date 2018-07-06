# configuration
#
# ~/.gdbinit

add-auto-load-safe-path /usr/lib/libthread_db-1.0.so
add-auto-load-safe-path /store/code/projects/kernel/linux/scripts/gdb/vmlinux-gdb.py
set auto-load libthread-db on

# set auto-load safe-path /
# set auto-load safe-path /usr/lib/libthread_db-1.0.so
# set debug auto-load on
# set verbose off

# directory ./src
# directory ./t
# source ~/.gdbinit-gef.py

# set disassembly intel
set history filename ~/.gdb_history
set history save on
set history size unlimited
set history remove-duplicates unlimited
set history expansion on
set print symbol-filename on
set print symbol on
set print array on
set print array-indexes on
set print frame-arguments all
set print entry-values if-needed
set print object on
set case-sensitive off

# out paging and thread control
set pagination off
# set height unlimited
# set non-stop on
# set schedule-multiple on
set backtrace past-entry on
set backtrace past-main on

# set tui border-kind ascii
set tui border-kind acs
# set tui border-mode normal
set tui border-mode bold
# set tui active-border-mode reverse
set tui active-border-mode bold-standout

# functions
#
define help-set
	if $argc > 0
		help set $arg0
		print
		show $arg0
	end
end
document help-set
	help-set <option>: List the help for <option> and prints current value
end

define locals-up
	set $n = ($arg0)
	set $upto = $n
	while $upto > 0
		info locals
		up-silently 1
		set $upto = $upto - 1
	end
	down-silently $n
end
document locals-up
	locals-up <n>: Lists local variables of <n> frames
end

define run-lind
	if $argc > 1
		run -a -- /lib/glibc/runnable-ld.so --library-path /lib/glibc /$arg1
		thread $arg0 attach
	else
		run -a -- /lib/glibc/runnable-ld.so --library-path /lib/glibc /fork
		if $argc > 0
			thread $arg0 attach
		end
	end
end
document run-lind
	run-lind [thread] [prog]: Runs /test_cases/[prog].nexe attached to [thread].
end

define segfault-address
	print $_siginfo._sifields._sigfault.si_addr
end
document segfault-address
	segfault-address: Print last fault address (from the $_siginfo structure).
end

define examine-instructions
	if $argc > 0
		x/20i $arg0
	else
		x/20i $_siginfo._sifields._sigfault.si_addr
	end
end
document examine-instructions
	examine-instructions [address]: Examine twenty instructions at [address] (defaults to fault address).
end

define examine-rip
	if $argc > 0
		x/20i $rip + $arg0
	else
		x/20i $rip
	end
end
document examine-rip
	examine-rip [offset]: Examine twenty instructions at %rip + [offset].
end

define print-representations
	if $argc > 0
		printf "[f] float: "
		print/f $arg0
		printf "[d] decimal: "
		print/d $arg0
		printf "[u] unsigned decimal: "
		print/u $arg0
		printf "[c] char: "
		print/c $arg0
		printf "[s] string: "
		print/s $arg0
		printf "[a] address: "
		print/a $arg0
		printf "[z] hex, zero padded on the left: "
		print/z $arg0
		printf "[t] binary: "
		print/t $arg0
	else
		printf "[f] float: "
		print/f $
		printf "[d] decimal: "
		print/d $
		printf "[u] unsigned decimal: "
		print/u $
		printf "[c] char: "
		print/c $
		printf "[s] string: "
		print/s $
		printf "[a] address: "
		print/a $
		printf "[z] hex, zero padded on the left: "
		print/z $
		printf "[t] binary: "
		print/t $
	end
end
document print-representations
	print-hex [value]: Print some common representations of [value] (defaults to $).
end

define examine-representations
	if $argc > 0
		set $i = 0
		while $i < $argc
			eval "set $cur = $arg%d", $i
			printf "[f] float: "
			x/f $cur
			printf "[d] decimal: "
			x/d $cur
			printf "[u] unsigned decimal: "
			x/u $cur
			printf "[c] char: "
			x/c $cur
			printf "[s] string: "
			x/s $cur
			printf "[a] address: "
			x/a $cur
			printf "[z] hex, zero padded on the left: "
			x/z $cur
			printf "[t] binary: "
			x/t $cur
			printf "[i] instruction: "
			x/i $cur
			set $i = $i + 1
		end
	else
		printf "[f] float: "
		x/f $_siginfo._sifields._sigfault.si_addr
		printf "[d] decimal: "
		x/d $_siginfo._sifields._sigfault.si_addr
		printf "[u] unsigned decimal: "
		x/u $_siginfo._sifields._sigfault.si_addr
		printf "[c] char: "
		x/c $_siginfo._sifields._sigfault.si_addr
		printf "[s] string: "
		x/s $_siginfo._sifields._sigfault.si_addr
		printf "[a] address: "
		x/a $_siginfo._sifields._sigfault.si_addr
		printf "[z] hex, zero padded on the left: "
		x/z $_siginfo._sifields._sigfault.si_addr
		printf "[t] binary: "
		x/t $_siginfo._sifields._sigfault.si_addr
		printf "[i] instruction: "
		x/i $_siginfo._sifields._sigfault.si_addr
	end
end
document examine-representations
	examine-hex [value]: Examine some common representations of [value] (defaults to fault address).
end

define dasm-on
	set disassemble-next-line on
end
document dasm-on
	dasm-on: Turn on disassemble next line.
end

define dasm-off
	set disassemble-next-line off
end
document dasm-off
	dasm-off: Turn off disassemble next line.
end

# aliases
#
alias -- asm = disassemble
alias -- anext = set disassemble-next-line
alias -- dy = dasm-on
alias -- dn = dasm-off
alias -- rlind = run-lind
alias -- iargs = info args
alias -- iregisters = info registers
alias -- ilocals = info locals
alias -- ithreads = info threads
alias -- tenable = tui enable
alias -- tdisable = tui disable
alias -- fault-address = segfault-address
alias -- sshow = segfault-address
alias -- xi = examine-instructions
alias -- pr = print-representations
alias -- xr = examine-representations
alias -- rip = examine-rip
alias -- lu = locals-up
alias -- hs = help-set

# vi:ft=gdb:
