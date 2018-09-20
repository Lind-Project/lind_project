#!/usr/bin/env zsh
#
# .zshrc - zsh interactive shell configuration

declare -a au_arr zle_arr zmod_arr zle_cust kbd_modes unset_arr set_arr ssh_hosts

kbd_modes+=(emacs vicmd viins)
au_arr+=(edit-command-line expand-absolute-path)
au_arr+=(down-line-or-beginning-search filter-select)
au_arr+=(insert-composed-char insert-unicode-char)
au_arr+=(regexp-replace run-help tetriscurses tetris)
au_arr+=(up-line-or-beginning-search which-command)
au_arr+=(zargs zed zmv)
zle_arr+=(bracketed-paste bracketed-paste-magic)
zle_arr+=(edit-command-line expand-absolute-path)
zle_arr+=(down-line-or-beginning-search execute-named-command)
zle_arr+=(insert-composed-char insert-unicode-char tetris)
zle_arr+=(up-line-or-beginning-search which-command)
zle_arr+=(zmv znt-history-widget znt-cd-widget znt-kill-widget)
zmod_arr+=(zsh/curses zsh/datetime zsh/db/gdbm zsh/deltochar zsh/mapfile)
zmod_arr+=(zsh/mathfunc zsh/net/socket zsh/net/tcp zsh/pcre zsh/terminfo)
zmod_arr+=(zsh/system zsh/zftp zsh/zprof zsh/zpty zsh/zselect)
zle_cust+=( fzf-locate-widge insert-composed-char)
zle_cust+=(append-clip-selection insert-clip-selection yank-clip-selection)
zle_cust+=(append-x-selection insert-x-selection yank-x-selection)
zle_cust+=(zle-backwards-delete-to-char zle-backwards-zap-to-char)
zle_cust+=(zle-compdef zle-emacs-keymap zle-fh zle-fman zle-less)
zle_cust+=(zle-list-binds zle-locate-widget zle-refresh-keymap)
zle_cust+=(zle-run-help zle-toggle-keymap zle-vi-keymap zle-vim)
zle_cust+=(zle-youtube-helper zle-zaw-help)
unset_arr+=(alwaystoend autolist automenu caseglob casematch checkjobs)
unset_arr+=(correctall extendedhistory flowcontrol histfcntllock)
unset_arr+=(globalexport globcomplete globsubst histignorespace)
unset_arr+=(histsavebycopy histverify multios nomatch printexitvalue)
unset_arr+=(sharehistory verbose)
set_arr+=(appendhistory autocd autopushd bareglobqual beep casematch)
set_arr+=(cbases chaselinks clobber completeinword correct cprecedences)
set_arr+=(equals extendedglob globassign globdots globstarshort)
set_arr+=(hashlistall histexpiredupsfirst histignorealldups)
set_arr+=(histignoredups histignoredups histlexwords histreduceblanks hup)
set_arr+=(incappendhistory interactivecomments kshglob kshoptionprint)
set_arr+=(listambiguous longlistjobs magicequalsubst octalzeroes)
set_arr+=(markdirs menucomplete monitor multibyte notify pathdirs)
set_arr+=(pipefail promptsubst pushdignoredups pushdminus pushdtohome)
set_arr+=(rematchpcre transientrprompt)

for opt in $unsetarr; do setopt "no$opt"; done
for opt in $setarr; do setopt "$opt"; done
. "$HOME/.profile"
. "$ZDOTDIR/.zfuncs"
. "$HOME/.aliases"
aliases[=]='noglob ='
autoload -U promptinit && promptinit
autoload -U +X compinit && compinit -u
grml_prompt_setup grml-large

# history stuff
if type zshreadhist &>/dev/null; then
	precmd_functions=(zshreadhist $precmd_functions)
fi
HISTFILE="$HOME/.zsh_history"
histchars='!^#'

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
bindkey -M emacs "\C-p" history-substring-search-up
bindkey -M emacs "\C-n" history-substring-search-down
bindkey -M emacs "\e[1~" beginning-of-line
bindkey -M emacs "\e\e[A" beginning-of-line
bindkey -M emacs "\e[4~" end-of-line
bindkey -M emacs "\e\e[B" end-of-line
bindkey -M emacs "\C-k" kill-whole-line
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
	bindkey -M "$mode" -s "\ea" " | awk "
	# alias gr='grep --color=auto'
	bindkey -M "$mode" -s "\eg" " | gr "
	# alias l='env LESS= less -CMNRis'
	bindkey -M "$mode" -s "\el" " | l "
	bindkey -M "$mode" -s "\es" " | sed "
	bindkey -M "$mode" "\e[1~" beginning-of-line
	bindkey -M "$mode" "\e[4~" end-of-line
	bindkey -M "$mode" "\ec" yank-x-selection
	bindkey -M "$mode" "\ev" insert-x-selection
	bindkey -M "$mode" "\eC" yank-clip-selection
	bindkey -M "$mode" "\eV" insert-clip-selection
	bindkey -M "$mode" "\e[17~" yank-x-selection
	bindkey -M "$mode" "\e[18~" insert-x-selection
	bindkey -M "$mode" "\e[" yank-x-selection
	bindkey -M "$mode" "\e]" insert-x-selection
	bindkey -M "$mode" "\e{" yank-clip-selection
	bindkey -M "$mode" "\e}" insert-clip-selection
	bindkey -M "$mode" "\ef" zle-fh
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
	# insert the last word from the previous
	# history event at the cursor position
	bindkey -M "$mode" "\e\\" insert-last-word
	bindkey -M "$mode" "\e[2~" insert-last-word
	bindkey -M "$mode" "\eE" tetris
	bindkey -M "$mode" "\e\er" znt-history-widget
	bindkey -M "$mode" "\e\et" znt-cd-widget
	bindkey -M "$mode" "\e\ek" znt-kill-widget
	# Ctrl+x h will show the completion context
	bindkey -M "$mode" "\C-x\C-h" _complete_help
	bindkey -M "$mode" "\C-xh" _complete_help
	bindkey -M "$mode" "\C-x\C-x" execute-named-command
	bindkey -M "$mode" "\C-xx" execute-named-command
	bindkey -M "$mode" "\C-b" emacs-backward-word
	bindkey -M "$mode" "\C-f" emacs-forward-word
	bindkey -M "$mode" "\eOA" up-line-or-beginning-search
	bindkey -M "$mode" "\e[A" up-line-or-beginning-search
	bindkey -M "$mode" "\eOB" down-line-or-beginning-search
	bindkey -M "$mode" "\e[B" down-line-or-beginning-search
	bindkey -M "$mode" "\e\e[D" emacs-backward-word
	bindkey -M "$mode" "\e[1;5D" emacs-backward-word
	bindkey -M "$mode" "\e[1;3D" emacs-backward-word
	bindkey -M "$mode" "\e[1;2D" emacs-backward-word
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
	bindkey -M "$mode" "$terminfo[kcud1]" emacs-backward-word
	bindkey -M "$mode" "$terminfo[kcuu1]" emacs-forward-word
	bindkey -M "$mode" "\e[6~" emacs-backward-word
	bindkey -M "$mode" "\e[5~" emacs-forward-word
	bindkey -M "$mode" "\e-" emacs-backward-word
	bindkey -M "$mode" "\e=" emacs-forward-word
	bindkey -M "$mode" "$(echotc kl)" backward-char
	bindkey -M "$mode" "$(echotc kr)" forward-char
	bindkey -M "$mode" "$(echotc ku)" up-line-or-beginning-search
	bindkey -M "$mode" "$(echotc kd)" down-line-or-beginning-search
	bindkey -M "$mode" "\e[3~" delete-char
	bindkey -M "$mode" "\ek" describe-key-briefly
	bindkey -M "$mode" "\C-xe" edit-command-line
	bindkey -M "$mode" "\C-x\C-e" edit-command-line
	bindkey -M "$mode" "\e\ey" zle-youtube-helper
	bindkey -M "$mode" "\eU" up-case-word
	bindkey -M "$mode" "\e\e\e" _history-complete-newer
	bindkey -M "$mode" "\e," spell-word
	bindkey -M "$mode" "\e<" zle-zaw-help
	bindkey -M "$mode" "\ew" which-command
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
	bindkey -M "$mode" "\e>" autosuggest-clear
	# f5: toggle keymap
	bindkey -M "$mode" "\e[15~" zle-toggle-keymap
	# f9: insert composed character
	# bindkey -M emacs "\e[19~" insert-composed-char
	bindkey -M "$mode" "\e;" fzf-completion
	bindkey -M "$mode" "\e\C-i" fasd-complete
	bindkey -M "$mode" "\e[Z" reverse-menu-complete
	bindkey -M "$mode" "\C-i" complete-word
	bindkey -M "$mode" "\ei" zle-locate-widget
	bindkey -M "$mode" "\er" fzf-history-widget
	bindkey -M "$mode" "\C-t" transpose-words
	bindkey -M "$mode" "\et" fzf-file-widget
	bindkey -M "$mode" "\eC" fzf-cd-widget
done

compdef _cpuled cpuled
compdef _ee ee
compdef _man fman
compdef _man man
compdef _gem gem
compdef _git fshow
compdef _man cppman
compdef _man tldr
compdef _pacaur apacman
compdef _pacaur pml
compdef _pacaur pspc
compdef _scrs scrs
compdef _scrs pscrs
compdef _uscrs uscrs
compdef _uscrs puscrs
compdef _texinfo info
compdef _vim v
compdef _pip pip
compdef _au au
compdef _au wa
compdef _pwns pwns
compdef azle=autoload
compdef e=vim
compdef g=git
compdef gnpm=npm
compdef p=perl
compdef pkgconf=pkg-config
compdef run=gcc
compdef xs=xsel
compdef _=sudo

# named directories
hash -d c="$CONFIG"
hash -d g="$HOME/lind_project/lind/lind_glibc"
hash -d git="$HOME/git"
hash -d inc="/usr/include"
hash -d initcpio="/usr/lib/initcpio/install"
hash -d k="$PROJECTS/kernel"
hash -d l="$HOME/lind_project"
hash -d man="$CONFIG/man"
hash -d n="$HOME/lind_project/native_client"
hash -d omz="/usr/share/oh-my-zsh"
hash -d plugins="/usr/share/oh-my-zsh/plugins"
hash -d repos="/store/repos"
hash -d rfc="/usr/share/doc/rfc"
hash -d systemd="/etc/systemd/system"
hash -d vim="$HOME/.vim"
hash -d z="$ZDOTDIR"
hash -d zc="$ZDOTDIR/completions"
hash -d zf="$ZDOTDIR/zfunctions"
hash -d zp="$ZDOTDIR/plugins"
hash -d zsh="$ZSH"

# parse ssh configuration
ssh_hosts=(${${(f@)$(cat ${HOME}/.ssh/{config,known_hosts}(N) /dev/null)}%%,*})
ssh_hosts=(${${(Mu)${${ssh_hosts##*/}##*@}##*.*}%%:*})
zstyle ':completion:*:(ssh|scp|sftp|rsync):*'	hosts $ssh_hosts
# run rehash on completion so new installed program are found automatically:
function _force_rehash() {
	((CURRENT == 1)) && rehash
	return 1
}
# only show single character options with '-'
zstyle -e ':completion:*:options'                    ignored-patterns '
	if [[ $PREFIX == - ]]; then
		reply=("--*");
	fi'
# completion tweaks
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
zstyle ':completion:*:correct:*'			insert-unambiguous true
zstyle ':completion:*:corrections'			format $'%{\e[0;31m%}%d (errors: %e)%{\e[0m%}'
zstyle ':completion:*:correct:*'			original true
zstyle ':completion:*:default'				list-colors "${(s.:.)LS_COLORS}"
zstyle ':completion:*:descriptions'			format $'%{\e[0;31m%}completing %B%d%b%{\e[0m%}'
zstyle ':completion:*:*:cd:*:directory-stack'		menu yes select
zstyle ':completion:*:expand:*'				tag-order all-expansions
zstyle ':completion:*:history-words'			list true
zstyle ':completion:*:history-words'			menu yes select
zstyle ':completion:*:history-words'			remove-all-dups yes
zstyle ':completion:*:history-words'			stop yes
zstyle ':completion:*:matches'				group 'yes'
zstyle ':completion:*'					group-name ''
zstyle ':completion:*'					menu select
zstyle ':completion:*:messages'				format '%d'
zstyle ':completion:*:options'				description 'yes'
zstyle ':completion:*:options'				auto-description '%d'
zstyle ':completion:*:processes'			command 'ps -au$USER'
zstyle ':completion:*:*:-subscript-:*'			tag-order indexes parameters
zstyle ':completion:*:-command-:*:'			verbose true
zstyle ':completion:*'					verbose true
zstyle ':completion:*:warnings'				format $'%{\e[0;31m%}no matches for:%{\e[0m%} %d'
zstyle ':completion:*:*:zcompile:*'			ignored-patterns '(*~|*.sw[a-p])'
zstyle ':completion:correct:'				prompt 'correct to: %e'
zstyle ':completion:*:processes-names'			command 'ps c -u ${USER} -o command | uniq'
zstyle ':completion:*:killall:*'			command 'ps -u ${USER} -o cmd'
zstyle ':completion:*:manuals*'				separate-sections true
zstyle ':completion:*:manuals*'				insert-sections   true
zstyle ':completion:*:man*'				menu yes select
zstyle ':completion:*:urls'				local 'www' 'public_html'
zstyle ':filter-select:highlight'			matched fg=yellow,standout
zstyle ':filter-select'					max-lines 10
zstyle ':filter-select'					rotate-list yes
zstyle ':filter-select'					case-insensitive yes
zstyle ':filter-select'					extended-search yes
if type -f wa &>/dev/null; then
	whencecmd=(wa)
else
	whencecmd=(whence -fv --)
fi
zstyle ':zle:which-command'				whence $whencecmd
zstyle ':completion:*'					matcher-list \
	'm:{a-z\-}={A-Z\_}' \
	'r:[^[:alpha:]]||[[:alpha:]]=** r:|=* m:{a-z\-}={A-Z\_}' \
	'r:|?=** m:{a-z\-}={A-Z\_}'

unset au_arr zle_arr zmod_arr zle_cust kbd_modes unset_arr set_arr ssh_hosts
