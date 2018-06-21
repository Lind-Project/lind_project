export PERIOD=10
integer -gx ZPLUG_COUNT=0
integer -gx ZPLUG_LOCK_TIMEOUT=0

__zplug::job::polling::periodic()
{
	if [[ -f $_zplug_lock[job] ]]; then
		case $ZPLUG_LOCK_TIMEOUT in
		1)
			ZPLUG_LOCK_TIMEOUT=0
			setopt monitor
			rm $_zplug_lock[job]
			;;
		*)
			if ((++ZPLUG_COUNT > PERIOD)); then
				ZPLUG_COUNT=0
				ZPLUG_LOCK_TIMEOUT=1
				setopt nomonitor
			fi
			;;
		esac
	else
		if [[ -o monitor ]]; then
		    return 0
		fi
		if setopt monitor; then
		    __zplug::log::write::info "turn monitor on"
		fi
	fi
}

add-zsh-hook periodic __zplug::job::polling::periodic
