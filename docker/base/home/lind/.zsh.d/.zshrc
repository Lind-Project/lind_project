#!/usr/bin/env zsh
#
# .zshrc - zsh interactive shell configuration

# catch EXIT, SIGINT, SIGQUIT, SIGTERM, and SIGTRAP signals for clean up
trap '{ cleanup; trap -; }' USR1 EXIT QUIT TERM
trap '{ cleanup; trap -; kill -INT $$; }' INT
_zsh_error="$(mktemp)"
# redirect errors to a temporary fd, and then append them to a log file
exec 9>&2
exec 2<>"$_zsh_error"
if [[ -f "$_zsh_error" ]]; then
	rm -f "$_zsh_error"
else
	cleanup
fi
# print arch linux news on startup
_show_news=0

# setopt arrays
#
() {
	local -a unsetarr setarr
	unsetarr+=(alwaystoend autolist automenu caseglob casematch checkjobs)
	unsetarr+=(correctall extendedhistory flowcontrol)
	unsetarr+=(histfcntllock globalexport globcomplete globsubst)
	unsetarr+=(histignorespace histsavebycopy histverify multios nomatch)
	unsetarr+=(printexitvalue sharehistory verbose)
	setarr+=(appendhistory autocd autopushd bareglobqual beep casematch)
	setarr+=(cbases chaselinks clobber completeinword correct cprecedences)
	setarr+=(equals extendedglob globassign globdots globstarshort)
	setarr+=(hashlistall histexpiredupsfirst histignorealldups)
	setarr+=(histignoredups histignoredups histlexwords histreduceblanks hup)
	setarr+=(incappendhistory interactivecomments kshglob kshoptionprint)
	setarr+=(listambiguous longlistjobs magicequalsubst octalzeroes)
	setarr+=(markdirs menucomplete monitor multibyte notify pathdirs)
	setarr+=(pipefail promptsubst pushdignoredups pushdminus pushdtohome)
	setarr+=(rematchpcre transientrprompt)
	# `setopt IGNORE_CLOSE_BRACES` breaks too many things :'(
	# setarr+=(ignoreclosebraces)
	() for 1 { setopt "no$1"; }  $unsetarr
	() for 1 { setopt "$1"; } $setarr
}
# emacs 19.29 or thereabouts stopped using a terminal type of "emacs" in
# shell buffers, and instead sets it to "dumb". zsh only kicks in its special
# i'm-inside-emacs initialization when the terminal type is "emacs".
[[ "$EMACS" == t ]] && unsetopt zle

# set emacs or vi as default
() for 1 { zle -N "$1"; } zle-keymap-select zle-line-init zle-line-finish
KEYTIMEOUT=20
bindkey -v
# initialize _km for zle widgets and set initial cursor color
# _km=emacs _emacs=main _vi=
_km=vi _emacs= _vi=main
setescapes
case "$_km" in
(vi)
	printf "$cblock"
	printf "$cgrey"
	;;
(emacs)
	printf "$cblock"
	printf "$cyellow"
	;;
esac
() for 1 { autoload -U "$1" && zle -N "$1"; } select-bracketed select-quoted

# text object for matching characters between matching pairs of brackets
() for 1 {
	bindkey -M viopp "$1" select-bracketed;
	bindkey -M visual "$1" select-bracketed;
} {a,i}${(s..)^:-'()[]{}<>bB'}
# text object for matching characters between a particular delimiter
() for 1 {
	bindkey -M viopp "$1" select-quoted
	bindkey -M visual "$1" select-quoted
} {a,i}${(s..)^:-\'\"\`\|,./:;-=+@}

# cache and history stuff
if type zshreadhist &>/dev/null; then
       precmd_functions=(zshreadhist $precmd_functions)
fi
# ^b: history expansion ^f: quick history substitution #: comment character
histchars='!^#'
# histchars=$'\2\6#'
HISTFILE="$HOME/.zsh_history"
ZSH_CACHE_DIR="${ZDOTDIR:-$HOME/.zsh.d}/cache"
[[ ! -d "$ZSH_CACHE_DIR" ]] && mkdir "$ZSH_CACHE_DIR"
zstyle ':completion:*'			use-cache yes
zstyle ':completion::complete:*'	cache-path "$ZSH_CACHE_DIR"
# zstyle ':completion:*'			rehash true
zstyle ':completion::complete:*'	rehash true
zstyle ':history-search-multi-word'	page-size 5
# Enable colors in prompt
autoload -U colors && colors
eval "$(dircolors -b)"
export CLICOLOR=1 REPORTTIME=5

# modules
#
() {
	local -a au_arr zle_arr zmod_arr zle_cust
	au_arr+=(edit-command-line expand-absolute-path)
	au_arr+=(down-line-or-beginning-search filter-select)
	au_arr+=(insert-composed-char insert-unicode-char)
	au_arr+=(regexp-replace run-help tetriscurses tetris)
	au_arr+=(up-line-or-beginning-search zargs zed zmv)
	# zle_arr+=(bracketed-paste bracketed-paste-magic)
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
	() for 1 { autoload -Uz "$1"; } $au_arr
	() for 1 { zle -N "$1"; } $zle_arr $zle_cust
	() for 1 { zmodload "$1"; } $zmod_arr
	# equiv of bash's "help"
	unalias run-help help 2>/dev/null
	alias help='run-help'
}

# zsh syntax highlighting
#
ZSH_HIGHLIGHT_PATTERNS+=('rm -rf' 'fg=white,bold,bg=red')
# Array declaring active highlighters names.
typeset -ga ZSH_HIGHLIGHT_HIGHLIGHTERS
# ZSH_HIGHLIGHT_HIGHLIGHTERS=(brackets cursor line main pattern regexp root)
ZSH_HIGHLIGHT_HIGHLIGHTERS=(brackets line main pattern regexp)

# git prompt
#
# Adapted from code found at <https://gist.github.com/1712320>.
# Modify the colors and symbols in these variables as desired.
GIT_PROMPT_SYMBOL="%{$fg[blue]%}±"
GIT_PROMPT_PREFIX="%{$fg[green]%}[%{$reset_color%}"
GIT_PROMPT_SUFFIX="%{$fg[green]%}]%{$reset_color%}"
GIT_PROMPT_AHEAD="%{$fg[red]%}ANUM%{$reset_color%}"
GIT_PROMPT_BEHIND="%{$fg[cyan]%}BNUM%{$reset_color%}"
GIT_PROMPT_MERGING="%{$fg[magenta]%}⚡︎%{$reset_color%}"
GIT_PROMPT_UNTRACKED="%{$fg[red]%}●%{$reset_color%}"
GIT_PROMPT_MODIFIED="%{$fg[yello w]%}●%{$reset_color%}"

# zsh autosuggestions
#
ZSH_AUTOSUGGEST_HIGHLIGHT_STYLE='fg=8'
ZSH_AUTOSUGGEST_BUFFER_MAX_SIZE=20
ZSH_AUTOSUGGEST_USE_ASYNC=1
# prefix to use when saving original versions of bound widgets
ZSH_AUTOSUGGEST_ORIGINAL_WIDGET_PREFIX=autosuggest-orig-
# - `default`: Chooses the most recent match.
# - `match_prev_cmd`: Chooses the most recent match whose preceding history
# ZSH_AUTOSUGGEST_STRATEGY=default
ZSH_AUTOSUGGEST_STRATEGY=match_prev_cmd
# widgets that modify the buffer and are not found in any of these
# arrays will fetch a new suggestion after they are invoked.
# widgets in this array will clear the suggestion when invoked.
# ZSH_AUTOSUGGEST_CLEAR_WIDGETS+=()
# widgets in this array will accept the suggestion when invoked.
# ZSH_AUTOSUGGEST_ACCEPT_WIDGETS+=()
# widgets in this array will execute the suggestion when invoked.
ZSH_AUTOSUGGEST_EXECUTE_WIDGETS+=()
# widgets in this array will partially accept the suggestion when invoked.
ZSH_AUTOSUGGEST_PARTIAL_ACCEPT_WIDGETS+=()
# widgets in this array will not trigger any custom behavior.
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(append-x-selection insert-x-selection)
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(yank-x-selection fzf-locate-widget)
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(insert-composed-char)
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(zle-backwards-delete-to-char)
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(zle-backwards-zap-to-char)
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(zle-compdef zle-emacs-keymap zle-fh zle-fman)
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(zle-less zle-list-binds zle-refresh-keymap)
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(zle-run-help zle-toggle-keymap zle-vi-keymap)
ZSH_AUTOSUGGEST_IGNORE_WIDGETS+=(zle-vim zle-youtube-helper zle-zaw-help)

## load VCS module
autoload -Uz vcs_info
if type vcs_info &>/dev/null; then
	zstyle ':vcs_info:*' enable git cvs svn
	zstyle ':vcs_info:*' disable bzr cdv darcs mtn svk tla
	zstyle ':vcs_info:*' check-for-changes true
	zstyle ':vcs_info:*:prompt:*' check-for-changes true
	zstyle ':vcs_info:*:prompt:*' stagedstr "%{$fg[green]%}*%{$reset_color%}"
	zstyle ':vcs_info:*:prompt:*' unstagedstr "%{$fg[red]%}*%{$reset_color%}"
	zstyle ':vcs_info:*:prompt:*' branchformat "%r"
	zstyle ':vcs_info:*:prompt:*' formats "%u%c%{$fg[green]%}[%b]%{$reset_color%}"
	zstyle ':vcs_info:*:prompt:*' nvcsformats ""
	zstyle ':vcs_info:*' actionformats \
		'%F{5}(%f%s%F{5})%F{3}-%F{5}[%F{2}%b%F{3}|%F{1}%a%F{5}]%f '
	zstyle ':vcs_info:*' formats \
		'%F{5}(%f%s%F{5})%F{3}-%F{5}[%F{2}%b%F{5}]%f '
	zstyle ':vcs_info:(sv[nk]|bzr):*' branchformat '%b%F{1}:%F{3}%r'
	zstyle ':vcs_info:git:*' actionformats \
		'%F{3}-%F{5}(%F{7}%r/%S%F{2}[%F{2}%m%F{9}%u%F{6}%c%F{2}]%F{5})%f '
	zstyle ':vcs_info:git:*' formats \
		'%F{3}-%F{5}(%F{7}%r/%S%F{2}[%F{2}%m%F{9}%u%F{6}%c%F{2}]%F{5})%f '
	precmd_functions=( vcs_info $precmd_functions )
	RPS1='$(check_last_exit_code)%(?,%F{green},%F{red} ┐❨ツ❩┌ )%f$(git_prompt_string)${vcs_info_msg_0_}'
else
	RPS1='$(check_last_exit_code)%(?,%F{green},%F{red} ┐❨ツ❩┌ )%f$(git_prompt_string)'
fi

# prepend zcompiled functions/completions to fpath
fpath[1,0]="${HOME}/.local/zsh/site-functions"
fpath[1,0]="${ZDOTDIR:-$HOME/.zsh.d}/zcomps.zwc"
fpath[1,0]="${ZDOTDIR:-$HOME/.zsh.d}/zfuncs.zwc"
autoload -U promptinit && promptinit
autoload -U +X compinit && compinit -u
autoload -U +X bashcompinit && bashcompinit -u
# autoload functions/completions in *.zwc files
() for 1 2 { autoload -Uwz "$1"; autoload -Uwz +X "$2"; } "${(M@z)fpath%%*.zwc}"
# autoload completion for systemctl subcommand compdefs
[[ "$(type _git)" =~ "autoload" ]] && autoload -Uz +X _git
[[ "$(type _pacman)" =~ "autoload" ]] && autoload -Uz +X _pacman
[[ "$(type _systemctl)" =~ "autoload" ]] && autoload -Uz +X _systemctl

# common PS1 section
PS1='$prompt_newline$(print -n "$bold_color$fg[grey]['
# avoid errors if proc isn't mounted
if [[ -d /proc ]]; then
	PS1+='$reset_color$fg[green]$((($('
	PS1+='sed -nr "s/MemTotal:\s+([0-9]+) kB/\1/Ip" /proc/meminfo) - $('
	PS1+='sed -nr "s/MemAvailable:\s+([0-9]+) kB/\1/Ip" /proc/meminfo))/1024))'
	PS1+='$reset_color$fg[yellow]/$(($('
	PS1+='sed -nr "s/MemTotal:\s+([0-9]+) kB/\1/Ip" /proc/meminfo)/1024))MB'
	PS1+='$bold_color$fg[grey]] [$fg[magenta]$(</proc/loadavg)"'
else
	PS1+='$fg[magenta]wat where is /proc"'
fi
PS1+='$bold_color$fg[grey]]) $bold_color$fg[grey]%}['
PS1+='$reset_color$fg[white]%}j%{$bold_color$fg[grey]%}:%{'
PS1+='$reset_color$fg[white]%}%j %l'
PS1+='$bold_color$fg[grey]%}]%{$reset_color$fg[cyan]%} '

# prompt char is cyan for normal users
if ((EUID)); then
	PS1+='$bold_color$fg[grey]%}[%{$bold_color$fg[green]%}%n@%m%{'
	PS1+='$bold_color$fg[grey]%}:%{$reset_color$fg[white]%}'
	PS1+='$SSH_TTY %{$bold_color$fg[red]%}+$SHLVL%{'
	PS1+='$bold_color$fg[grey]%}] %{$bold_color$fg[yellow]%}%~'
	PS1+='$prompt_newline%{$bold_color$fg[grey]%}(%{'
	PS1+='$reset_color$fg[white]%}!!%{$bold_color$fg[grey]%}:%{'
	PS1+='$reset_color$fg[white]%}%!%{$bold_color$fg[grey]%})%{'
	PS1+='$reset_color$fg[cyan]%} %(!.#.$) %{$reset_color%}'
else
	# prompt char is red for root
	PS1+='$bold_color$fg[grey]%}[%{$bold_color$fg[red]%}%n@%m%{'
	PS1+='$bold_color$fg[grey]%}:%{$reset_color$fg[white]%}'
	PS1+='$SSH_TTY %{$bold_color$fg[green]%}+$SHLVL%{'
	PS1+='$bold_color$fg[grey]%}] %{$bold_color$fg[yellow]%}%~'
	PS1+='$prompt_newline%{$bold_color$fg[grey]%}(%{'
	PS1+='$reset_color$fg[white]%}!!%{$bold_color$fg[grey]%}:%{'
	PS1+='$reset_color$fg[white]%}%!%{$bold_color$fg[grey]%})%{'
	PS1+='$bold_color$fg[red]%} %(!.#.$) %{$reset_color%}'
fi

# bash specific
[[ -f /etc/profile.d/cnf.sh ]] && \
	. /etc/profile.d/cnf.sh
[[ -f /usr/share/bash-completion/completions/dkms ]] && \
	. /usr/share/bash-completion/completions/dkms
# zsh specific
[[ -d "${ZDOTDIR:-$HOME/.zsh.d}"/plugins ]] && \
	{ for i in "${ZDOTDIR:-$HOME/.zsh.d}"/plugins/enabled/*.zsh; . "$i"; }
[[ -f "${HOME}/perl5/perlbrew/etc/perlbrew-completion.bash" ]] && \
	. "${HOME}/perl5/perlbrew/etc/perlbrew-completion.bash"
# setup python-virtualenvwrapper
[[ -f /usr/bin/virtualenvwrapper.sh ]] && \
	. /usr/bin/virtualenvwrapper.sh
# [[ -f /usr/bin/virtualenvwrapper_lazy.sh ]] && \
#         . /usr/bin/virtualenvwrapper_lazy.sh

# prompt rice
if ((_show_news)) && [[ "$(hostname)" != compiler ]]; then
	news_short
fi

# "Is the internet on fire?" status reports
() {
	local -a host=(host -W 1 -t) dig=(dig +short +timeout=1)
	local -a cmdline=($host txt istheinternetonfire.com)
	# local -a cmdline=($dig txt istheinternetonfire.com)
	local muhcow="$(print -l - /usr/share/cows/*(.:r:t) | sort -R | head -1)"
	$cmdline | cut -f2 -d'"' | cowsay -f "$muhcow" -W 50
	print;
}

if type fasd &>/dev/null; then
	eval "$(fasd --init auto)"
fi

if type filter-select &>/dev/null; then
	filter-select -i
	bindkey -M filterselect "\C-e" accept-search
fi

if type zplug >/dev/null 2>&1; then
	# zplug "hlissner/zsh-autopair"
	# zplug "kennethreitz/autoenv"
	# zplug "jocelynmallon/zshmarks"
	# zplug "StackExchange/blackbox"
	# zplug "aeruder/zirc"
	# zplug "tj/git-extras"
	# zplug "stedolan/jq", from:gh-r, as:command, rename-to:jq
	# zplug "b4b4r07/emoji-cli", on:"stedolan/jq"
	# zplug "zdharma/fast-syntax-highlighting", defer:2
	zplug "oknowton/zsh-dwim"
	zplug "zsh-users/zsh-autosuggestions"
	zplug "zsh-users/zsh-history-substring-search"
	# zplug "zsh-users/zsh-syntax-highlighting", defer:2, at:tmp
	zplug "zsh-users/zsh-syntax-highlighting", defer:2
	# zplug "b4b4r07/zsh-vimode-visual", defer:3
	# zplug 'zplug/zplug', hook-build:'zplug --self-manage'
	if ! zplug check --verbose; then
		print -r - "Install? [y/N]: "
		if read -sq; then zplug install; fi
	fi
	zplug load --verbose
fi

# user command aliases and shortcuts
[[ -f "${HOME}/.aliases" ]] && \
	. "${HOME}/.aliases"
aliases[=]='noglob ='
safetytoggle -n

# 'literal trigger' & fzf-completion keybind to start fuzzy completion
export FZF_COMPLETION_TRIGGER="**"
# export FZF_COMPLETION_TRIGGER="//"
export fzf_default_completion="complete-word"
# export fzf_default_completion="expand-or-complete-prefix"

# custom bindkey commands
#
# oh god prepare yourself
bindkey -M emacs "\C-p" history-substring-search-up
bindkey -M emacs "\C-n" history-substring-search-down
# for inside tmux
bindkey -M emacs "\e[1~" beginning-of-line
bindkey -M emacs "\e\e[A" beginning-of-line
bindkey -M emacs "\e[4~" end-of-line
bindkey -M emacs "\e\e[B" end-of-line
bindkey -M emacs "\C-k" kill-whole-line
## bind k and j for VI mode
bindkey -M vicmd "k" history-substring-search-up
bindkey -M vicmd "j" history-substring-search-down
# bindkey -M vicmd "k" up-line-or-beginning-search
# bindkey -M vicmd "j" down-line-or-beginning-search
bindkey -M vicmd "u" undo
# bindkey -M vicmd "u" vi-undo-change
bindkey -M vicmd "Y" vi-yank-eol
bindkey -M vicmd "P" insert-x-selection
bindkey -M vicmd "p" append-x-selection
bindkey -M viins "\C-p" history-substring-search-up
bindkey -M viins "\C-n" history-substring-search-down
bindkey -M viins "jj" vi-cmd-mode

# vimode-visual bindings
_modes=(emacs vicmd viins)
if [[ -n "${(M)keymaps#vivis}" ]]; then
	bindkey -M vicmd 'V'  vi-vlines-mode
	bindkey -M vicmd 'v'  vi-visual-mode
	bindkey -M vivis ' '  vi-visual-forward-char
	bindkey -M vivis ','  vi-visual-rev-repeat-find
	bindkey -M vivis '0'  vi-visual-bol
	bindkey -M vivis ';'  vi-visual-repeat-find
	bindkey -M vivis 'B'  vi-visual-backward-blank-word
	bindkey -M vivis 'C'  vi-visual-substitute-lines
	bindkey -M vivis 'D'  vi-visual-kill-and-vicmd
	bindkey -M vivis 'E'  vi-visual-forward-blank-word-end
	bindkey -M vivis 'F'  vi-visual-find-prev-char
	bindkey -M vivis 'G'  vi-visual-goto-line
	bindkey -M vivis 'I'  vi-visual-insert-bol
	bindkey -M vivis 'J'  vi-visual-join
	bindkey -M vivis 'O'  vi-visual-exchange-points
	bindkey -M vivis 'R'  vi-visual-substitute-lines
	bindkey -M vivis 'S ' vi-visual-surround-space
	bindkey -M vivis "S'" vi-visual-surround-squote
	bindkey -M vivis 'S"' vi-visual-surround-dquote
	bindkey -M vivis 'S(' vi-visual-surround-parenthesis
	bindkey -M vivis 'S)' vi-visual-surround-parenthesis
	bindkey -M vivis 'T'  vi-visual-find-prev-char-skip
	bindkey -M vivis 'U'  vi-visual-uppercase-region
	bindkey -M vivis 'V'  vi-visual-exit-to-vlines
	bindkey -M vivis 'W'  vi-visual-forward-blank-word
	bindkey -M vivis 'Y'  vi-visual-yank
	bindkey -M vivis '^M' vi-visual-yank
	bindkey -M vivis '^[' vi-visual-exit
	bindkey -M vivis 'b'  vi-visual-backward-word
	bindkey -M vivis 'c'  vi-visual-change
	bindkey -M vivis 'd'  vi-visual-kill-and-vicmd
	bindkey -M vivis 'e'  vi-visual-forward-word-end
	bindkey -M vivis 'f'  vi-visual-find-next-char
	bindkey -M vivis 'gg' vi-visual-goto-first-line
	bindkey -M vivis 'h'  vi-visual-backward-char
	bindkey -M vivis 'j'  vi-visual-down-line
	bindkey -M vivis 'jj' vi-visual-exit
	bindkey -M vivis 'k'  vi-visual-up-line
	bindkey -M vivis 'l'  vi-visual-forward-char
	bindkey -M vivis 'o'  vi-visual-exchange-points
	bindkey -M vivis 'p'  vi-visual-put
	bindkey -M vivis 'r'  vi-visual-replace-region
	bindkey -M vivis 't'  vi-visual-find-next-char-skip
	bindkey -M vivis 'u'  vi-visual-lowercase-region
	bindkey -M vivis 'v'  vi-visual-eol
	bindkey -M vivis 'w'  vi-visual-forward-word
	bindkey -M vivis 'y'  vi-visual-yank
	_modes+=(vivis)
fi

() for 1 {
	# use \2 and \6 for history expansion
	# bindkey -M "$1" "\C-b" self-insert
	# bindkey -M "$1" "\C-f" self-insert
	bindkey -M "$1" "\C-w" backward-kill-word
	bindkey -M "$1" "\e\C-m" self-insert-unmeta
	bindkey -M "$1" "\eh" zle-run-help
	bindkey -M "$1" "\eu" undo
	bindkey -M "$1" "\ey" yank-pop
	bindkey -M "$1" "\C-y" yank
	bindkey -M "$1" "\C-q" push-line
	bindkey -M "$1" "\C-k" kill-whole-line
	bindkey -M "$1" "\ed" kill-word
	bindkey -M "$1" "\e[3~" delete-char
	bindkey -M "$1" "\C-h" backward-delete-char
	bindkey -M "$1" "\C-?" backward-delete-char
	bindkey -M "$1" "\e\C-?" backward-kill-word
	bindkey -M "$1" "\C-o" accept-line-and-down-history
	# bindkey -sM "$1" "\e[23~" "*"
	bindkey -M "$1" "\e[23~" zle-list-binds
	bindkey -M "$1" "\C-z" fancy-ctrl-z
	bindkey -M "$1" "\ep" expand-absolute-path
	bindkey -M "$1" "\eo" zle-less
	# insert the last word from the previous history event at the cursor position
	bindkey -M "$1" "\e\\" insert-last-word
	bindkey -M "$1" "\eE" tetris
	bindkey -M "$1" "\e\er" znt-history-widget
	bindkey -M "$1" "\e\et" znt-cd-widget
	bindkey -M "$1" "\e\ek" znt-kill-widget
	## Ctrl+x h will show the completion context
	bindkey -M "$1" "\C-x\C-h" _complete_help
	bindkey -M "$1" "\C-xh" _complete_help
	bindkey -M "$1" "\C-x\C-x" execute-named-command
	bindkey -M "$1" "\C-xx" execute-named-command

	# movement
	bindkey -M "$1" "\eOA" up-line-or-beginning-search
	bindkey -M "$1" "\e[A" up-line-or-beginning-search
	bindkey -M "$1" "\eOB" down-line-or-beginning-search
	bindkey -M "$1" "\e[B" down-line-or-beginning-search
	bindkey -M "$1" "\eOD" emacs-backward-word
	bindkey -M "$1" "\e\e[D" emacs-backward-word
	bindkey -M "$1" "\e[1;5D" emacs-backward-word
	bindkey -M "$1" "\e[1;3D" emacs-backward-word
	bindkey -M "$1" "\e[1;2D" emacs-backward-word
	bindkey -M "$1" "\eOC" emacs-forward-word
	bindkey -M "$1" "\e\e[C" emacs-forward-word
	bindkey -M "$1" "\e[1;5C" emacs-forward-word
	bindkey -M "$1" "\e[1;3C" emacs-forward-word
	bindkey -M "$1" "\e[1;2C" emacs-forward-word
	bindkey -M "$1" "\e[7~" beginning-of-line
	bindkey -M "$1" "\e[1;5B" beginning-of-line
	bindkey -M "$1" "\e[1;3B" beginning-of-line
	bindkey -M "$1" "\e[1;2B" beginning-of-line
	bindkey -M "$1" "\C-a" beginning-of-line
	bindkey -M "$1" "\e[8~" end-of-line
	bindkey -M "$1" "\e[1;5A" end-of-line
	bindkey -M "$1" "\e[1;3A" end-of-line
	bindkey -M "$1" "\e[1;2A" end-of-line
	bindkey -M "$1" "\C-e" end-of-line
	# bind up and down arrow keys (compatibility fallback
	# for ubuntu 12.04, fedora 21, and macosx 10.9 users)
	bindkey -M "$1" "$terminfo[kcuu1]" history-substring-search-up
	bindkey -M "$1" "$terminfo[kcud1]" history-substring-search-down
	bindkey -M "$1" "\e[5~" history-substring-search-up
	bindkey -M "$1" "\e[6~" history-substring-search-down
	bindkey -M "$1" "\e-" history-substring-search-up
	bindkey -M "$1" "\e=" history-substring-search-down
	# fixes from http://zsh.sourceforge.net/faq/zshfaq03.html#l25
	bindkey -M "$1" "$(echotc kl)" backward-char
	bindkey -M "$1" "$(echotc kr)" forward-char
	bindkey -M "$1" "$(echotc ku)" up-line-or-beginning-search
	bindkey -M "$1" "$(echotc kd)" down-line-or-beginning-search

	bindkey -M "$1" "\e[3~" delete-char
	bindkey -M "$1" "\ek" describe-key-briefly
	bindkey -M "$1" "\C-xe" edit-command-line
	bindkey -M "$1" "\C-x\C-e" edit-command-line
	bindkey -M "$1" "\e\ey" zle-youtube-helper
	bindkey -M "$1" "\eU" up-case-word
	bindkey -M "$1" "\e\e\e" _history-complete-newer
	bindkey -M "$1" "\e," zaw
	bindkey -M "$1" "\e<" zle-zaw-help
	bindkey -M "$1" "\ew" zle-backwards-delete-to-char
	bindkey -M "$1" "\ee" delete-to-char
	bindkey -M "$1" "\eOP" zle-less
	bindkey -M "$1" "\eOQ" zle-vim
	bindkey -M "$1" "\eOR" insert-unicode-char
	bindkey -M "$1" "\eOS" zle-compdef
	bindkey -M "$1" "\e[P" delete-char
	bindkey -M "$1" "\C-r" redo
	# call fman() on current cmdline after word-splitting
	bindkey -M "$1" "\e/" zle-fman
	bindkey -M "$1" "\e?" where-is
	bindkey -M "$1" "^Xi" insert-unicode-char
	bindkey -M "$1" "\C-x\C-i" insert-unicode-char
	bindkey -M "$1" "\e>" autosuggest-clear
	# f5: toggle keymap
	bindkey -M "$1" "\e[15~" zle-toggle-keymap
	bindkey -M "$1" "\e[17~" yank-x-selection
	bindkey -M "$1" "\e[18~" insert-x-selection
	bindkey -M "$1" "\e[" yank-x-selection
	bindkey -M "$1" "\e]" insert-x-selection
	# bindkey -M "$1" "\e[18~" append-x-selection
	# f9: insert composed character
	# bindkey -M emacs "\e[19~" insert-composed-char

	bindkey -M "$1" "\e;" fzf-completion
	bindkey -M "$1" "\e\C-i" fasd-complete
	# bindkey -M "$1" "\e[Z" fzf-complete-f
	# bindkey -M "$1" "\e[Z" fasd-complete-d
	bindkey -M "$1" "\e[Z" reverse-menu-complete
	bindkey -M "$1" "\C-i" "$fzf_default_completion"
	bindkey -M "$1" "\ei" fzf-locate-widget
	bindkey -M "$1" "\er" fzf-history-widget
	bindkey -M "$1" "\C-t" transpose-words
	bindkey -M "$1" "\et" fzf-file-widget
	# f8: type a command and zsh-dwim will attempt to transform your command.
	if zle -la | grep -q dwim; then
		bindkey -M "$1" "\C-u" dwim
		bindkey -M "$1" "\e[19~" dwim
	fi
} $_modes

# more uglyness soz
#
# custom compdefs with generated and hardcoded arrays
() {
	local cgasm_str dgpg_str hi_str high_str reptyr_str modprobe_str
	local -a gnu_generic_cmds asmcmds dbpkgs kmods pubkeys seckeys nacl_cmds

	gnu_generic_cmds+=(${$(print -r - $HOME/lind_project/native_client/tools/out/nacl-sdk/bin/*(.)):t})
	gnu_generic_cmds+=(as auracle autopep8 autopep8-python2 basename bash bsdtar)
	gnu_generic_cmds+=(calcc canto-curses canto-daemon canto-remote catdoc ccache)
	gnu_generic_cmds+=(cd2raw cdcd cdr2raw cdrdao cd-read cdu cgasm chromium)
	gnu_generic_cmds+=(ci co col colordiff compton configure conky cower cpanm)
	gnu_generic_cmds+=(cppcheck cpulimit crontab ctags curl define dmidecode)
	gnu_generic_cmds+=(dumpasn1 expac fasd file flac2all fusermount-glusterfs)
	gnu_generic_cmds+=(fusermount3 elftoc free fzf gnome-keyring-daemon gpg-agent)
	gnu_generic_cmds+=(help2man highlight hping hsetroot icdiff install keyring)
	gnu_generic_cmds+=(kid3-cli kid3-qt ld lighttpd2 ln lrz lua lz4 maim more)
	gnu_generic_cmds+=(mountpoint mpd muttprint mv named neomutt netstat netstat)
	gnu_generic_cmds+=(newsbeuter node nohup objconv objdump oomox-cli optipng)
	gnu_generic_cmds+=(pacconf pactree paste pisg pstree qemu-img qemu-nbd reptyr)
	gnu_generic_cmds+=(resolvconf rfc rg rlwrap rmdir rmlint rst2man rst2man2)
	gnu_generic_cmds+=(saldl scan-build seq shred sox split stat st stjerm)
	gnu_generic_cmds+=(strings supybot swapon systool tdrop termite test tic)
	gnu_generic_cmds+=(tload transmission-cli transmission-create)
	gnu_generic_cmds+=(transmission-daemon transmission-edit transmission-get)
	gnu_generic_cmds+=(transmission-gtk transmission-qt transmission-remote)
	gnu_generic_cmds+=(transmission-remote-cli transmission-remote-cli)
	gnu_generic_cmds+=(transmission-remote-gtk transmission-show transset-df)
	gnu_generic_cmds+=(updatedb urxvtc urxvtcdurxvtd vanitygen vimpager)
	gnu_generic_cmds+=(x11vnc xbindkeys xsel youtube-dl)

	if type cgasm &>/dev/null; then
		asmcmds+=(${(o)$({ cgasm -f '.*' | perl -alne '
				BEGIN{ my @cmds; }
				push @cmds, split(/ /, lc $F[0] =~ y|/| |r);
				END{ print join " ", @cmds;}'; } 2>/dev/null)})
	fi
	if type pacman &>/dev/null; then
		dbpkgs+=(${(fo@)$(pacman -Qq 2>/dev/null)})
	fi
	if type gpg2 &>/dev/null; then
		pubkeys+=(${${(Mo)$(gpg2 -k --no-default-keyring \
			--list-options no-show-photos 2>/dev/null):%<*>}//(<|>)/})
		seckeys+=(${${(Mo)$(gpg2 -K --no-default-keyring \
			--list-options no-show-photos  2>/dev/null):%<*>}//(<|>)/})
	fi
	if type find &>/dev/null; then
		kmods+=(${${(f0@)$(find /usr/lib/modules/$(uname -r) \
			-type f -name '*.ko.gz' 2>/dev/null)%.ko.gz}##*/})
	fi

	cgasm_str+=$'_arguments "*:arg:_default" ":assembly instruction:('
	cgasm_str+="${asmcmds[*]}"
	cgasm_str+=')" -- '
	# dgpg_str+=$'_arguments "*:arg:_default" ":public key:('
	# dgpg_str+="${pubkeys[*]}"
	dgpg_str+=$'_arguments "*:arg:_default" ":secret keys:('
	dgpg_str+="${seckeys[*]}"
	dgpg_str+=$')" -- '
	hi_str+=$'_arguments '
	hi_str+=$'":syntax:_files '
	hi_str+=$'-W \'/usr/share/highlight/langDefs/\' '
	hi_str+=$'-g \'*.lang(:r)\'" '
	hi_str+=$'"*:file:_files" -- '
	high_str+=$'_arguments '
	high_str+=$'":theme:_files '
	high_str+=$'-W \'/usr/share/highlight/themes\' '
	high_str+=$'-g \'*.theme(:r)\'" '
	high_str+=$'":syntax:_files '
	high_str+=$'-W \'/usr/share/highlight/langDefs\' '
	high_str+=$'-g \'*.lang(:r)\'" '
	high_str+=$'":out format: '
	high_str+=$'(html xhtml latex tex rtf odt ansi xterm256 truecolor bbcode pango svg)" '
	high_str+=$'"*:file:_files" -- '
	qpc_str+=$'_arguments "*:packages:('
	qpc_str+="${dbpkgs[*]}"
	qpc_str+=$')" -- '
	reptyr_str+=$'_arguments "*:arg:_default" ":processe:_pids" -- '
	modprobe_str+=$'_arguments "*:arg:_default" ":modules:('
	modprobe_str+="${kmods[*]}"
	modprobe_str+=$')" -- '

	() for 1 {
		if ! type -f _${1##*-} &>/dev/null; then
			compdef _gnu_generic ${1##*-}
		fi
		compdef $1=${1##*-}
	} $nacl_cmds
	() for 1 {
		if ! type -f _$1 &>/dev/null; then
			compdef _gnu_generic $1
		fi
	} $gnu_generic_cmds

	compdef "$cgasm_str" cgasm
	compdef "$dgpg_str" dgpg
	compdef "$hi_str" hi
	compdef "$high_str" high
	compdef "$modprobe_str" modprobe
	compdef "$qpc_str" qpc
	compdef "$reptyr_str" reptyr

}

compdef _cpuled cpuled
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
compdef cg=cgasm
compdef e=vim
compdef g=git
compdef gnpm=npm
compdef oomox=oomox-cli
compdef p=perl
compdef pkgconf=pkg-config
compdef run=gcc
compdef xs=xsel
compdef _=sudo
compdef meminfo=free

# named directories
hash -d a="${HOME}/code/aur"
hash -d audio="/sdxc/audio"
hash -d b="${HOME}/bin/"
hash -d calibre="/sdxc/calibre"
hash -d code="${P:-/store/code/projects}/school"
hash -d c="${C:-/store/dotfiles}"
hash -d d="${P:-/store/code/projects}/linux/Documentation"
hash -d djzomg="/sdxc/Music/djzomg"
hash -d efi="/boot/efi/EFI"
hash -d euler="${HOME}/code/euler"
hash -d g="$HOME/lind_project/lind/lind_glibc"
hash -d git="${HOME}/git"
hash -d hdd="/run/media/alyptik/toshiba1TB"
hash -d inc="/usr/include"
hash -d initcpio="/usr/lib/initcpio/install"
hash -d k="${P:-/store/code/projects}/kernel"
hash -d l="$HOME/lind_project"
hash -d linux="${P:-/store/code/projects}/linux"
hash -d magnets="${C:-/store/dotfiles}/magnets"
hash -d man="${C:-/store/dotfiles}/man"
hash -d music="/store/music"
hash -d n="$HOME/lind_project/native_client"
hash -d nginx="/etc/nginx"
hash -d omz="/usr/share/oh-my-zsh"
hash -d p="${P:-/store/code/projects}"
hash -d plugins="/usr/share/oh-my-zsh/plugins"
hash -d prose="/store/writing"
hash -d r="$HOME/lind_project/repy/repy"
hash -d repos="/store/repos"
hash -d rfc="/usr/share/doc/rfc"
hash -d s="/sdxc/school"
hash -d sdxc="/sdxc"
hash -d surfraw="/usr/lib/surfraw"
hash -d stuff="/hdd"
hash -d systemd="/etc/systemd/system"
hash -d t="/store/torrents"
hash -d tt="/hdd/torrents"
hash -d vim="${HOME}/.vim"
hash -d vm="/run/media/alyptik/vm"
hash -d wanderlust="/hdd/wanderlust"
hash -d words="${C:-/store/dotfiles}/unixstories"
hash -d www="/srv/http"
hash -d z="${ZDOTDIR:-$HOME/.zsh.d}"
hash -d zc="${ZDOTDIR:-$HOME/.zsh.d}/completions"
hash -d zf="${ZDOTDIR:-$HOME/.zsh.d}/zfunctions"
hash -d znc="/var/lib/znc/.znc/moddata/log/alyptik/freenode/"
hash -d zp="${ZDOTDIR:-$HOME/.zsh.d}/plugins"
hash -d zsh="$ZSH"

# Define word separators (for stuff like backward-word, forward-word, backward-kill-word,..)
WORDCHARS=
# WORDCHARS='_-*~'
# WORDCHARS='*?_-.[]~=/&;!#$%^ (){}<>'

# Completion tweaks
() {
	# parse ssh configuration
	local -a _ssh_hosts
	_ssh_hosts=(${${(f@)$(cat ${HOME}/.ssh/{config,known_hosts}(N) /dev/null)}%%,*})
	_ssh_hosts=(${${(Mu)${${_ssh_hosts##*/}##*@}##*.*}%%:*})
	zstyle ':completion:*:(ssh|scp|sftp|rsync):*'	hosts $_ssh_hosts
}

# only show single character options with -
# zstyle -e ':completion:*:options'			ignored-patterns '
#         if [[ $PREFIX == - ]]; then
#                 reply=("--*");
#         fi'

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

# 0 -- vanilla completion (abc => abc)
# 1 -- smart case completion (abc => Abc)
# 2 -- word flex completion (abc => A-big-Car)
# 3 -- full flex completion (abc => ABraCadabra)
zstyle ':completion:*'					matcher-list \
	'm:{a-z\-}={A-Z\_}' \
	'r:[^[:alpha:]]||[[:alpha:]]=** r:|=* m:{a-z\-}={A-Z\_}' \
	'r:|?=** m:{a-z\-}={A-Z\_}'
	# '' \
	# 'm:{a-z\-}={A-Z\_}' \
	# 'r:[^[:alpha:]]||[[:alpha:]]=** r:|=* m:{a-z\-}={A-Z\_}' \
	# 'r:|?=** m:{a-z\-}={A-Z\_}'

# recent (as of Dec 2007) zsh versions are able to provide descriptions
# for commands (read: 1st word in the line) that it will list for the user
# to choose from. The following disables that, because it's not exactly fast.
zstyle ':completion:*:-command-:*:'			verbose true
# provide verbose completion information
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
# provide .. as a completion
# zstyle ':completion:*'					special-dirs ..

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

# end of .zshrc config
#
# all dankness must come to an end :(
kill -USR1 $$

