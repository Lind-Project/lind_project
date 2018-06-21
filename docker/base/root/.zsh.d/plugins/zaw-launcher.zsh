#!/bin/zsh
#
# zaw-launcher.zsh
#
# launcher script to start zaw as command

# source zaw.zsh
local this_file="$0"
local cur_dir="${this_file:A:h}"
source "${cur_dir}/zaw.zsh"

if [[ "$@" =~ (-v|--version) ]]; then
	print "zaw v1.0r294.e9d232f"
	exit
fi

# parse arguments
do_eval=0

while getopts ':eh' opt; do
    case "${opt}" in
        e)
            do_eval=1
            ;;

        h|\?)
            print \
"Usage: $0 [options] [source name]

Options:
 -h     show this help
 -e     eval result string

Keybinds:
 ^X:			trigger zaw
 enter:			accept-line (execute default action)
 meta + enter:		accept-search (execute alternative action)
 Tab:			select-action
 ^G:			send-break
 ^H, backspace:		backward-delete-char
 ^F, right key:		forward-char
 ^B, left key:		backward-char
 ^A:			beginning-of-line
 ^E:			end-of-line
 ^W:			backward-kill-word
 ^K:			kill-line
 ^U:			kill-whole-line
 ^N, down key:		down-line-or-history (select next item)
 ^P, up key:		up-line-or-history (select previous item)
 ^V, page up key:	forward-word (page down)
 ^[V, page down key:	backward-word (page up)
 ^[<, home key:		beginning-of-history (select first item)
 ^[>, end key:		end-of-history (select last item)
"
            exit
            ;;
    esac
done

if (( OPTIND > 1 )); then
    shift $(( OPTIND - 1 ))
fi

zaw_args=()
if [[ $# > 0 && "${zaw_sources[$1]}" != "" ]]; then
    zaw_args+="${zaw_sources[$1]}"
fi


# use zle-line-init to start zaw right after vared
function zle-line-init() {
    zle zaw "${(@)zaw_args}"

    # return from vared
    zle accept-line
}
zle -N zle-line-init

vared -c cmd

if (( do_eval )); then
    eval "${cmd}"
else
    print "${cmd}"
fi
