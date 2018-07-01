#!/usr/bin/env zsh
#
# .zshrc - zsh interactive shell configuration

declare -a au_arr zle_arr zmod_arr zle_cust kbd_modes
kbd_modes+=(emacs vicmd viins)
au_arr+=(edit-command-line expand-absolute-path)
au_arr+=(down-line-or-beginning-search filter-select)
au_arr+=(insert-composed-char insert-unicode-char)
au_arr+=(regexp-replace run-help tetriscurses tetris)
au_arr+=(up-line-or-beginning-search zargs zed zmv)
zle_arr+=(edit-command-line expand-absolute-path)
zle_arr+=(down-line-or-beginning-search execute-named-command)
zle_arr+=(insert-composed-char insert-unicode-char tetris)
zle_arr+=(up-line-or-beginning-search zmv znt-history-widget)
zle_arr+=(znt-cd-widget znt-kill-widget)
zmod_arr+=(zsh/curses zsh/datetime zsh/db/gdbm zsh/deltochar zsh/mapfile)
zmod_arr+=(zsh/mathfunc zsh/net/socket zsh/net/tcp zsh/pcre zsh/terminfo)
zmod_arr+=(zsh/system zsh/zftp zsh/zprof zsh/zpty zsh/zselect)
zle_cust+=(append-x-selection fzf-locate-widge insert-composed-char)
zle_cust+=(insert-x-selection yank-x-selection)
zle_cust+=(zle-backwards-delete-to-char zle-backwards-zap-to-char)
zle_cust+=(zle-compdef zle-emacs-keymap zle-fh zle-fman zle-less)
zle_cust+=(zle-list-binds zle-refresh-keymap zle-run-help zle-toggle-keymap)
zle_cust+=(zle-vi-keymap zle-vim zle-youtube-helper zle-zaw-help)

. "$HOME/.profile"
. "$HOME/.zfuncs"
. "$HOME/.aliases"
aliases[=]='noglob ='
grml_prompt_setup grml-large

# history stuff
if type zshreadhist &>/dev/null; then
	precmd_functions=(zshreadhist $precmd_functions)
fi
HISTFILE="$HOME/.zsh_history"
histchars='!^#'
# ^b: history expansion ^f: quick history substitution #: comment character
# histchars=$'\2\6#'
# bindkey "\C-b" self-insert
# bindkey "\C-f" self-insert
# for mode in $kbd_modes; do
#         bindkey -M "$mode" "\C-b" self-insert
#         bindkey -M "$mode" "\C-f" self-insert
# done

# cache stuff
ZSH_CACHE_DIR="$HOME/.cache/zsh"
[[ ! -d "$ZSH_CACHE_DIR" ]] && mkdir "$ZSH_CACHE_DIR"
zstyle ':completion:*'			use-cache yes
zstyle ':completion::complete:*'	cache-path "$ZSH_CACHE_DIR"
zstyle ':completion::complete:*'	rehash true
zstyle ':completion:*'			rehash true
zstyle ':history-search-multi-word'	page-size 5
autoload -U colors && colors
eval "$(dircolors -b)"
export CLICOLOR=1 REPORTTIME=5

# autoloads, modules, and zle functions
for func in $au_arr; do
	autoload -Uz "$func"
done
for func in $zle_arr $zle_cust; do
	zle -N "$func"
done
for mod in $zmod_arr; do
	zmodload "$mod"
done
# equiv of bash's "help"
unalias run-help help 2>/dev/null
alias help='run-help'

# custom keybinds
bindkey -M emacs "\e[1~" beginning-of-line
bindkey -M emacs "\e\e[A" beginning-of-line
bindkey -M emacs "\e[4~" end-of-line
bindkey -M emacs "\e\e[B" end-of-line
bindkey -M emacs "\C-k" kill-whole-line
# vim "ci/vi/ca/va" motions
bindkey -M emacs "\C-p" history-substring-search-up
bindkey -M emacs "\C-n" history-substring-search-down
# bind k and j for VI mode
bindkey -M vicmd "k" history-substring-search-up
bindkey -M vicmd "j" history-substring-search-down
bindkey -M vicmd "u" undo
bindkey -M vicmd "Y" vi-yank-eol
bindkey -M vicmd "P" insert-x-selection
bindkey -M vicmd "p" append-x-selection
bindkey -M viins "\C-p" history-substring-search-up
bindkey -M viins "\C-n" history-substring-search-down
bindkey -M viins "jj" vi-cmd-mode
for func in select-bracketed select-quoted; do
	autoload -Uz "$func" && zle -N "$func"
done
# text object for matching characters between matching pairs of brackets
for char in {a,i}${(s..)^:-'()[]{}<>bB'}; do
	bindkey -M viopp "$char" select-bracketed;
	bindkey -M visual "$char" select-bracketed;
done
for char in {a,i}${(s..)^:-\'\"\`\|,./:;-=+@}; do
	bindkey -M viopp "$char" select-quoted
	bindkey -M visual "$char" select-quoted
done
for mode in $kbd_modes; do
	bindkey -M "$mode" "\C-w" backward-kill-word
	bindkey -M "$mode" "\e\C-m" self-insert-unmeta
	bindkey -M "$mode" "\eh" zle-run-help
	bindkey -M "$mode" "\eu" undo
	bindkey -M "$mode" "\ey" yank-pop
	bindkey -M "$mode" "\C-y" yank
	bindkey -M "$mode" "\C-q" push-line
	bindkey -M "$mode" "\C-k" kill-whole-line
	bindkey -M "$mode" "\ed" kill-word
	bindkey -M "$mode" "\e[3~" delete-char
	bindkey -M "$mode" "\C-h" backward-delete-char
	bindkey -M "$mode" "\C-?" backward-delete-char
	bindkey -M "$mode" "\e\C-?" backward-kill-word
	bindkey -M "$mode" "\C-o" accept-line-and-down-history
	bindkey -M "$mode" "\e[23~" zle-list-binds
	bindkey -M "$mode" "\C-z" fancy-ctrl-z
	bindkey -M "$mode" "\ep" expand-absolute-path
	bindkey -M "$mode" "\eo" zle-less
	# insert the last word from the previous history event at the cursor position
	bindkey -M "$mode" "\e\\" insert-last-word
	bindkey -M "$mode" "\eE" tetris
	# ^x h will show the completion context
	bindkey -M "$mode" "\C-x\C-h" _complete_help
	bindkey -M "$mode" "\C-xh" _complete_help
	bindkey -M "$mode" "\C-x\C-x" execute-named-command
	bindkey -M "$mode" "\C-xx" execute-named-command
	bindkey -M "$mode" "\eOA" up-line-or-beginning-search
	bindkey -M "$mode" "\e[A" up-line-or-beginning-search
	bindkey -M "$mode" "\eOB" down-line-or-beginning-search
	bindkey -M "$mode" "\e[B" down-line-or-beginning-search
	bindkey -M "$mode" "\eOD" emacs-backward-word
	bindkey -M "$mode" "\e\e[D" emacs-backward-word
	bindkey -M "$mode" "\e[1;5D" emacs-backward-word
	bindkey -M "$mode" "\e[1;3D" emacs-backward-word
	bindkey -M "$mode" "\e[1;2D" emacs-backward-word
	bindkey -M "$mode" "\eOC" emacs-forward-word
	bindkey -M "$mode" "\e\e[C" emacs-forward-word
	bindkey -M "$mode" "\e[1;5C" emacs-forward-word
	bindkey -M "$mode" "\e[1;3C" emacs-forward-word
	bindkey -M "$mode" "\e[1;2C" emacs-forward-word
	bindkey -M "$mode" "\e[7~" beginning-of-line
	bindkey -M "$mode" "\e[1;5B" beginning-of-line
	bindkey -M "$mode" "\e[1;3B" beginning-of-line
	bindkey -M "$mode" "\e[1;2B" beginning-of-line
	bindkey -M "$mode" "\C-a" beginning-of-line
	bindkey -M "$mode" "\e[8~" end-of-line
	bindkey -M "$mode" "\e[1;5A" end-of-line
	bindkey -M "$mode" "\e[1;3A" end-of-line
	bindkey -M "$mode" "\e[1;2A" end-of-line
	bindkey -M "$mode" "\C-e" end-of-line
	bindkey -M "$mode" "$terminfo[kcuu1]" history-substring-search-up
	bindkey -M "$mode" "$terminfo[kcud1]" history-substring-search-down
	bindkey -M "$mode" "\e[5~" history-substring-search-up
	bindkey -M "$mode" "\e[6~" history-substring-search-down
	bindkey -M "$mode" "\e-" history-substring-search-up
	bindkey -M "$mode" "\e=" history-substring-search-down
	bindkey -M "$mode" "$(echotc kl)" backward-char
	bindkey -M "$mode" "$(echotc kr)" forward-char
	bindkey -M "$mode" "$(echotc ku)" up-line-or-beginning-search
	bindkey -M "$mode" "$(echotc kd)" down-line-or-beginning-search
	bindkey -M "$mode" "\e[3~" delete-char
	# alt+k plus a key will show what that key is bound to
	bindkey -M "$mode" "\ek" describe-key-briefly
	bindkey -M "$mode" "\C-xe" edit-command-line
	bindkey -M "$mode" "\C-x\C-e" edit-command-line
	bindkey -M "$mode" "\eU" up-case-word
	bindkey -M "$mode" "\e\e\e" _history-complete-newer
	bindkey -M "$mode" "\ew" zle-backwards-delete-to-char
	bindkey -M "$mode" "\ee" delete-to-char
	bindkey -M "$mode" "\eOP" zle-less
	bindkey -M "$mode" "\eOQ" zle-vim
	bindkey -M "$mode" "\eOR" insert-unicode-char
	bindkey -M "$mode" "\eOS" zle-compdef
	bindkey -M "$mode" "\e[P" delete-char
	bindkey -M "$mode" "\C-r" redo
	# call fman() on current cmdline after word-splitting
	bindkey -M "$mode" "\e/" zle-fman
	bindkey -M "$mode" "\e?" where-is
	bindkey -M "$mode" "^Xi" insert-unicode-char
	bindkey -M "$mode" "\C-x\C-i" insert-unicode-char
	# f5: toggle keymap
	bindkey -M "$mode" "\e[15~" zle-toggle-keymap
	bindkey -M "$mode" "\e[17~" yank-x-selection
	bindkey -M "$mode" "\e[18~" insert-x-selection
	bindkey -M "$mode" "\e[" yank-x-selection
	bindkey -M "$mode" "\e]" insert-x-selection
done

# run rehash on completion so new installed program are found automatically:
function _force_rehash() {
	((CURRENT == 1)) && rehash
	return 1
}
# try to be smart about when to use what completer...
zstyle -e ':completion:*'				completer '
	if [[ $_last_try != "$HISTNO$BUFFER$CURSOR" ]]; then
		_last_try="$HISTNO$BUFFER$CURSOR"
		reply=(_complete _expand _match _prefix _correct _approximate)
	else
		reply=(_force_rehash _oldlist _ignored _files)
	fi'
zstyle ':acceptline'					nocompwarn true
# allow one error for every two characters typed in approximate completer
zstyle ':completion:*:approximate:'			max-errors 'reply=("$((($#PREFIX+$#SUFFIX)/3))" numeric)'
# zstyle ':completion:*:approximate:'			max-errors 5 numeric
# start menu completion only if it could find no unambiguous initial string
zstyle ':completion:*:correct:*'			insert-unambiguous true
zstyle ':completion:*:corrections'			format $'%{\e[0;31m%}%d (errors: %e)%{\e[0m%}'
zstyle ':completion:*:correct:*'			original true
# activate color-completion
zstyle ':completion:*:default'				list-colors "${(s.:.)LS_COLORS}"
# format on completion
zstyle ':completion:*:descriptions'			format $'%{\e[0;31m%}completing %B%d%b%{\e[0m%}'
# complete 'cd -<tab>' with menu
zstyle ':completion:*:*:cd:*:directory-stack'		menu yes select
# insert all expansions for expand completer
zstyle ':completion:*:expand:*'				tag-order all-expansions
zstyle ':completion:*:history-words'			list true
# ignore duplicate entries
zstyle ':completion:*:history-words'			menu yes select
zstyle ':completion:*:history-words'			remove-all-dups yes
zstyle ':completion:*:history-words'			stop yes
# separate matches into groups
zstyle ':completion:*:matches'				group 'yes'
zstyle ':completion:*'					group-name ''
zstyle ':completion:*'					menu select
zstyle ':completion:*:messages'				format '%d'
# describe options in full
zstyle ':completion:*:options'				description 'yes'
zstyle ':completion:*:options'				auto-description '%d'
# on processes completion complete all user processes
zstyle ':completion:*:processes'			command 'ps -au$USER'
# offer indexes before parameters in subscripts
zstyle ':completion:*:*:-subscript-:*'			tag-order indexes parameters
# word-flex completion
zstyle ':completion:*'					matcher-list \
	'm:{a-z\-}={A-Z\_}' \
	'r:[^[:alpha:]]||[[:alpha:]]=** r:|=* m:{a-z\-}={A-Z\_}' \
	'r:|?=** m:{a-z\-}={A-Z\_}'
# provide verbose completion information
zstyle ':completion:*:-command-:*:'			verbose true
zstyle ':completion:*'					verbose true
# set format for warnings
zstyle ':completion:*:warnings'				format $'%{\e[0;31m%}no matches for:%{\e[0m%} %d'
# define files to ignore for zcompile
zstyle ':completion:*:*:zcompile:*'			ignored-patterns '(*~|*.sw[a-p])'
# zstyle ':completion:*:*:zcompile:*'			ignored-patterns '(*~|*.zwc)'
zstyle ':completion:correct:'				prompt 'correct to: %e'
# Ignore completion functions for commands you don't have:
# zstyle ':completion::(^approximate*):*:functions' ignored-patterns '_*'
# Provide more processes in completion of programs like killall:
zstyle ':completion:*:processes-names'			command 'ps c -u ${USER} -o command | uniq'
zstyle ':completion:*:killall:*'			command 'ps -u ${USER} -o cmd'
# complete manual by their section
zstyle ':completion:*:manuals'				separate-sections true
zstyle ':completion:*:manuals'				insert-sections   true
zstyle ':completion:*:man*'				menu yes select
# command for process lists, the local web server details and host completion
zstyle ':completion:*:urls'				local 'www' 'public_html'
# filter-select options
zstyle ':filter-select:highlight'			matched fg=yellow,standout
# use $LINES - 10 for filter-select
zstyle ':filter-select'					max-lines 10
# enable rotation for filter-select
zstyle ':filter-select'					rotate-list yes
# enable case-insensitive search
zstyle ':filter-select'					case-insensitive yes
# see below
zstyle ':filter-select'					extended-search yes

unset au_arr zle_arr zmod_arr zle_cust kbd_modes
