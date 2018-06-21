#!/usr/bin/env zsh
#
# .zshrc
#
# Zsh configuration file

# Catch EXIT, SIGINT, SIGQUIT, SIGTERM, and SIGTRAP signals for clean up
trap '{ cleanup; trap -; }' USR1 EXIT
trap '{ cleanup; trap -; kill -INT $$; }' INT
trap '{ cleanup; trap -; kill -QUIT $$; }' QUIT
trap '{ cleanup; trap -; kill -TERM $$; }' TERM
# Redirect errors to a temporary fd, and then append them to a log file
ZSH_ERROR="$(mktemp)"
exec 9>&2
exec 2<>"$ZSH_ERROR"
[[ -f "$ZSH_ERROR" ]] && rm -f "$ZSH_ERROR" || cleanup

## Set/unset options
() {
	local -a unsetarr setarr
	unsetarr+=(alwaystoend autolist automenu caseglob casematch checkjobs)
	unsetarr+=(correctall extendedhistory flowcontrol histfcntllock globalexport)
	unsetarr+=(globcomplete globsubst histignorespace histsavebycopy)
	unsetarr+=(histverify multios nomatch printexitvalue sharehistory verbose)
	setarr+=(appendhistory autocd autopushd bareglobqual beep casematch cbases)
	setarr+=(chaselinks clobber completeinword correct cprecedences equals)
	setarr+=(extendedglob globassign globdots globstarshort histexpiredupsfirst)
	setarr+=(histignorealldups histignoredups histlexwords histreduceblanks)
	setarr+=(hup incappendhistory interactivecomments kshglob kshoptionprint)
	setarr+=(listambiguous longlistjobs magicequalsubst octalzeroes)
	setarr+=(markdirs menucomplete monitor multibyte notify pathdirs pipefail)
	setarr+=(promptsubst pushdignoredups pushdminus pushdtohome rematchpcre)
	() for 1 { unsetopt "$1"; }  $unsetarr
	() for 1 { setopt "$1"; } $setarr
}

# Emacs 19.29 or thereabouts stopped using a terminal type of "emacs" in
# shell buffers, and instead sets it to "dumb". Zsh only kicks in its special
# I'm-inside-emacs initialization when the terminal type is "emacs".
[[ "$EMACS" == t ]] && unsetopt zle

## Set emacs or vi as default
bindkey -e
() for 1 { zle -N "$1" } zle-keymap-select zle-line-init zle-line-finish
# theme: 0 = clint / 1 = custom PS1 / * = wtf are u doing
_theme=1
# Initialize _km for ZLE widgets and set initial cursor color
_km=emacs _emacs=main _vi=
setescapes
case "$_km" in
(vi)
	printf "$cblock"; printf "$cgrey" ;;
(emacs)
	printf "$cblock"; printf "$cyellow" ;;
esac

# Cache setup
ZSH_CACHE_DIR="${ZDOTDIR:-$HOME/.zsh.d}/cache"
[[ ! -d "$ZSH_CACHE_DIR" ]] && mkdir "$ZSH_CACHE_DIR"
zstyle ':completion:*'			rehash true
zstyle ':completion:*'			use-cache yes
zstyle ':completion::complete:*'	cache-path "$ZSH_CACHE_DIR"
zstyle ':history-search-multi-word'	page-size 5
# Enable colors in prompt
autoload -U colors && colors
eval "$(dircolors -b)"
export CLICOLOR=1 REPORTTIME=5

# History stuff
HISTFILE="${HOME}/.zsh_history"
type zshreadhist &>/dev/null && precmd_functions=(zshreadhist $precmd_functions)

# zmodules
() {
	local -a au_arr zle_arr zmod_arr
	au_arr+=(expand-absolute-path up-line-or-beginning-search)
	au_arr+=(down-line-or-beginning-search filter-select run-help)
	au_arr+=(regexp-replace edit-command-line nsert-unicode-char)
	au_arr+=(insert-composed-char tetriscurses tetris zargs zed zmv)
	# zle_arr+=(bracketed-paste bracketed-paste-magic)
	zle_arr+=(edit-command-line expand-absolute-path)
	zle_arr+=(up-line-or-beginning-search down-line-or-beginning-search)
	zle_arr+=(znt-history-widget znt-cd-widget znt-kill-widget)
	zle_arr+=(insert-unicode-char tetris zmv)
	zmod_arr+=(zsh/datetime zsh/mapfile zsh/mathfunc)
	zmod_arr+=(zsh/terminfo zsh/deltochar zsh/curses)
	zmod_arr+=(zsh/net/socket zsh/system zsh/net/tcp)
	zmod_arr+=(zsh/zftp zsh/zprof zsh/zpty zsh/zselect)
	zmod_arr+=(zsh/pcre zsh/db/gdbm zsh/deltochar)
	() for 1 { autoload -Uz "$1"; } $au_arr
	() for 1 { zle -N "$1"; } $zle_arr
	() for 1 { zmodload "$1"; } $zmod_arr
}

# equiv of bash's "help"
unalias run-help help 2>/dev/null
alias help='run-help'

#AUTOPAIR_INHIBIT_INIT=${AUTOPAIR_INHIBIT_INIT:-}
#AUTOPAIR_BETWEEN_WHITESPACE=${AUTOPAIR_BETWEEN_WHITESPACE:-}
typeset -gA AUTOPAIR_PAIRS
#AUTOPAIR_PAIRS=('`' '`' "'" "'" '"' '"' '{' '}' '[' ']' '(' ')' '<' '>')
AUTOPAIR_PAIRS=('`' '`' "'" "'" '"' '"' '{' '}' '[' ']' '(' ')')
## For example, if AUTOPAIR_LBOUNDS[braces]="[a-zA-Z]", then braces
## {([) won't be autopaired if the cursor follows an alphabetical character.
## Individual delimiters can be used too. Setting
## AUTOPAIR_RBOUNDS['{']="[0-9]" will cause { specifically to not be
## autopaired when the cursor precedes a number.
typeset -gA AUTOPAIR_LBOUNDS
AUTOPAIR_LBOUNDS=('`' '`')
AUTOPAIR_LBOUNDS[all]='[.:/\!]'
AUTOPAIR_LBOUNDS[quotes]='[]})a-zA-Z0-9]'
AUTOPAIR_LBOUNDS[braces]=''
AUTOPAIR_LBOUNDS["'"]="'"
typeset -gA AUTOPAIR_RBOUNDS
AUTOPAIR_RBOUNDS[all]='[[{(<,.:?/%$!a-zA-Z0-9]'
AUTOPAIR_RBOUNDS[quotes]='[a-zA-Z0-9]'
AUTOPAIR_RBOUNDS[braces]=''
## Array declaring active highlighters names.
typeset -ga ZSH_HIGHLIGHT_HIGHLIGHTERS
ZSH_HIGHLIGHT_HIGHLIGHTERS=(main brackets line pattern root)
ZSH_HIGHLIGHT_HIGHLIGHTERS_DIR="${ZDOTDIR:-${HOME}/.zsh.d}/plugins/highlighters"
## Zsh autosuggest defaults
ZSH_AUTOSUGGEST_HIGHLIGHT_STYLE='fg=8'
## Prefix to use when saving original versions of bound widgets
ZSH_AUTOSUGGEST_ORIGINAL_WIDGET_PREFIX=autosuggest-orig-
ZSH_AUTOSUGGEST_STRATEGY=default
ZSH_AUTOSUGGEST_BUFFER_MAX_SIZE=25
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
GIT_PROMPT_STAGED="%{$fg[green]%}●%{$reset_color%}"

case "$_theme" in
(0)
	# continue scanning
	type prompt_clint_setup &>/dev/null && prompt_clint_setup || _theme=1 ;|

(1)
	# common PS1 section
	PS1='$prompt_newline%{$(echo -en "$reset_color$fg[green]"$(($(:
		)$(sed -n "s/MemFree:[[:space:]]\+\([0-9]\+\) kB/\1/Ip" $(:
		)/proc/meminfo)/1024))"$(:
		)$reset_color$fg[yellow]/"$(($(:
		)$(sed -n "s/MemTotal:[[:space:]]\+\([0-9]\+\) kB/\1/Ip" $(:
		)/proc/meminfo)/1024))MB"		$(:
		)$reset_color$fg[magenta]$(</proc/loadavg)")$(:
		)$prompt_newline$bold_color$fg[grey]%}[%{$(:
		)$reset_color$fg[white]%}$$:$PPID %j:%l%{$(:
		)$bold_color$fg[grey]%}]%{$reset_color$fg[cyan]%}	$(:
		)%D{%a %d %b %I:%M:%S%P}'
	# fallback theme if no /proc
	if [[ ! -d /proc ]]; then
		type prompt_clint_setup &>/dev/null && prompt_clint_setup
	elif (( EUID != 0 )); then
		# normal colors
		PS1+='$bold_color$fg[grey]%}[%{$bold_color$fg[green]%}%n@%m%{$bold_color$fg[grey]%}:%{$(:
			)$reset_color$fg[white]%}${SSH_TTY} %{$bold_color$fg[red]%}+${SHLVL}%{$(:
			)$bold_color$fg[grey]%}] %{$bold_color$fg[yellow]%}%~%{$(:
			)$reset_color$fg[yellow]%} $prompt_newline($SHLVL:%!)%{$(:
			)$reset_color$fg[cyan]%} %(!.#.$) %{$reset_color%}'
	else
		# If root, print the prompt character in red. Otherwise, print the prompt in cyan.
		PS1+='$bold_color$fg[grey]%}[%{$bold_color$fg[red]%}%n@%m%{$bold_color$fg[grey]%}:%{$(:
			)$reset_color$fg[white]%}${SSH_TTY} %{$bold_color$fg[green]%}+${SHLVL}%{$(:
			)$bold_color$fg[grey]%}] %{$bold_color$fg[yellow]%}%~%{$(:
			)$reset_color$fg[yellow]%} $prompt_newline($SHLVL:%!)%{$(:
			)$bold_color$fg[red]%} %(!.#.$) %{$reset_color%}'
	fi ;;

(*)
	# ?????????? how did you hit this wtf
	type prompt_clint_setup >/dev/null 2>&1 && prompt_clint_setup ;;
esac

## load VCS module
autoload -Uz vcs_info
if type vcs_info >/dev/null 2>&1; then
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
fpath[1,0]="${ZDOTDIR:-$HOME/.zsh.d}/zcomps.zwc"
fpath[1,0]="${ZDOTDIR:-$HOME/.zsh.d}/zfuncs.zwc"
autoload -U promptinit && promptinit
autoload -U +X compinit && compinit -u
autoload -U +X bashcompinit && bashcompinit -u
# bash specific
[[ -f /etc/profile.d/cnf.sh ]] && \
	. /etc/profile.d/cnf.sh
[[ -f /usr/share/bash-completion/completions/dkms ]] && \
	. /usr/share/bash-completion/completions/dkms
# zsh specific
[[ -d "${ZDOTDIR:-$HOME/.zsh.d}"/plugins ]] && \
	{ for i in "${ZDOTDIR:-$HOME/.zsh.d}"/plugins/enabled/*.zsh; do . "$i"; done; }
[[ -f "${HOME}/perl5/perlbrew/etc/perlbrew-completion.bash" ]] && \
	. "${HOME}/perl5/perlbrew/etc/perlbrew-completion.bash"
[[ -f "${HOME}/.aliases" ]] && \
	. "${HOME}/.aliases"
# autoload functions/completions in *.zwc files
() for 1 2 { autoload -Uwz "$1"; autoload -Uwz +X "$2"; } "${(M@z)fpath%%*.zwc}"

news_short
safetytoggle -n
() {
	# "Is the internet on fire?" status reports
	local muhcow="$(print -l -- /usr/share/cows/*(.:r:t) | sort -R | head -1)"
	host -t txt istheinternetonfire.com | cut -f 2 -d '"' | cowsay -f "$muhcow" -W 50
}

# autoload completion for systemctl subcommand compdefs
[[ "$(type _systemctl)" =~ "autoload" ]] && autoload -Uz +X _systemctl
type fasd &>/dev/null && eval "$(fasd --init auto)"

if type filter-select &>/dev/null; then
	filter-select -i
	bindkey -M filterselect '^E' accept-search
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
	zplug "oknowton/zsh-dwim"
	zplug "zsh-users/zsh-autosuggestions"
	zplug "zsh-users/zsh-syntax-highlighting"
	zplug "zsh-users/zsh-history-substring-search"
	zplug 'zplug/zplug', hook-build:'zplug --self-manage'
	if ! zplug check --verbose; then
		print -- "Install? [y/N]: "
		if read -sq; then zplug install; fi
	fi
	zplug load --verbose
fi

zle -N zle-youtube-helper
zle -N zle-fman
zle -N zle-compdef
zle -N zle-toggle-keymap
zle -N zle-emacs-keymap
zle -N zle-vi-keymap
zle -N append-x-selection
zle -N insert-x-selection
zle -N yank-x-selection
zle -N fzf-locate-widget
zle -N insert-composed-char
zle -N zle-backwards-delete-to-char
zle -N zle-backwards-zap-to-char
zle -N zle-zaw-help
zle -N zle-less
zle -N zle-vim
zle -N zle-fh

# FZF fuzzy completion
export fzf_default_completion="expand-or-complete-prefix"
# 'literal trigger' & fzf-completion keybind to start fuzzy completion
export FZF_COMPLETION_TRIGGER='//'
# export FZF_COMPLETION_TRIGGER='**'

# bind P and N for EMACS mode
bindkey -M emacs '^P' history-substring-search-up
bindkey -M emacs '^N' history-substring-search-down
# for inside tmux
bindkey -M emacs "[1~" beginning-of-line
bindkey -M emacs "[A" beginning-of-line
bindkey -M emacs "[4~" end-of-line
bindkey -M emacs "[B" end-of-line
bindkey -M emacs "\C-k" kill-whole-line
bindkey -M emacs "u" undo
bindkey -M vicmd "u" vi-undo-change
bindkey -M viins "u" vi-undo-change
bindkey -M vicmd "u" undo
## bind k and j for VI mode
#bindkey -M vicmd 'k' history-substring-search-up
#bindkey -M vicmd 'j' history-substring-search-down
bindkey -M vicmd 'k' up-line-or-beginning-search
bindkey -M vicmd 'j' down-line-or-beginning-search
bindkey -M vicmd "[3~" delete-char
bindkey -M viins "[3~" delete-char

# oh god prepare yourself
#
# custom bindkey commands
() for 1 {
	# F11 inserts a literal '*'
	bindkey -sM "$1" "[23~" "*"
	bindkey -M "$1" "p" expand-absolute-path
	bindkey -M "$1" "o" zle-less
	# insert the last word from the previous history event at the cursor position
	bindkey -M "$1" "\" insert-last-word
	bindkey -M "$1" "E" tetris
	bindkey -M "$1" "r" znt-history-widget
	bindkey -M "$1" "t" znt-cd-widget
	bindkey -M "$1" "k" znt-kill-widget
	## Ctrl+x h will show the completion context
	bindkey -M "$1" "\C-x\C-h" _complete_help
	bindkey -M "$1" "\C-xh" _complete_help

	# movement
	bindkey -M "$1" "OA" up-line-or-beginning-search
	bindkey -M "$1" "[A" up-line-or-beginning-search
	bindkey -M "$1" "OB" down-line-or-beginning-search
	bindkey -M "$1" "[B" down-line-or-beginning-search
	bindkey -M "$1" '^[[A' up-line-or-beginning-search
	bindkey -M "$1" '^[[B' down-line-or-beginning-search
	bindkey -M "$1" "OD" backward-word
	bindkey -M "$1" "[D" backward-word
	bindkey -M "$1" "[1;5D" backward-word
	bindkey -M "$1" "[1;3D" backward-word
	bindkey -M "$1" "[1;2D" backward-word
	bindkey -M "$1" "OC" forward-word
	bindkey -M "$1" "[C" forward-word
	bindkey -M "$1" "[1;5C" forward-word
	bindkey -M "$1" "[1;3C" forward-word
	bindkey -M "$1" "[1;2C" forward-word
	bindkey -M "$1" "[7~" beginning-of-line
	bindkey -M "$1" "[1;5B" beginning-of-line
	bindkey -M "$1" "[1;3B" beginning-of-line
	bindkey -M "$1" "[8~" end-of-line
	bindkey -M "$1" "[1;5A" end-of-line
	bindkey -M "$1" "[1;3A" end-of-line
	bindkey -M "$1" "[1;2B" beginning-of-line
	bindkey -M "$1" "[1;2A" end-of-line
	# bind UP and DOWN arrow keys (compatibility fallback
	# for Ubuntu 12.04, Fedora 21, and MacOSX 10.9 users)
	bindkey -M "$1" "$terminfo[kcuu1]" history-substring-search-up
	bindkey -M "$1" "$terminfo[kcud1]" history-substring-search-down
	bindkey -M "$1" "[5~" history-substring-search-up
	bindkey -M "$1" "[6~" history-substring-search-down
	bindkey -M "$1" "-" history-substring-search-up
	bindkey -M "$1" "=" history-substring-search-down
	# Fixes from http://zsh.sourceforge.net/FAQ/zshfaq03.html#l25
	bindkey -M "$1" "$(echotc kl)" backward-char
	bindkey -M "$1" "$(echotc kr)" forward-char
	bindkey -M "$1" "$(echotc ku)" up-line-or-beginning-search
	bindkey -M "$1" "$(echotc kd)" down-line-or-beginning-search

	bindkey -M "$1" "[3~" delete-char
	bindkey -M "$1" "k" describe-key-briefly
	bindkey -M "$1" "\C-xe" edit-command-line
	bindkey -M "$1" "\C-x\C-e" edit-command-line
	bindkey -M "$1" "y" zle-youtube-helper
	bindkey -M "$1" "U" up-case-word
	bindkey -M "$1" "" _history-complete-newer
	bindkey -M "$1" "," zaw
	bindkey -M "$1" "<" zle-zaw-help
	bindkey -M "$1" "w" zle-backwards-delete-to-char
	bindkey -M "$1" "e" delete-to-char
	bindkey -M "$1" "OP" zle-less
	bindkey -M "$1" "OQ" zle-vim
	bindkey -M "$1" "OR" insert-unicode-char
	bindkey -M "$1" "OS" zle-compdef
	bindkey -M "$1" "[P" delete-char
	bindkey -M "$1" "\C-r" redo
	## Call fman() on current cmdline after word-splitting
	bindkey -M "$1" "/" zle-fman
	bindkey -M "$1" "?" where-is
	bindkey -M "$1" "^Xi" insert-unicode-char
	bindkey -M "$1" "\C-x\C-i" insert-unicode-char
	bindkey -M "$1" ">" autosuggest-clear
	## F5: Toggle keymap
	# bindkey -M "$1" "k" zle-toggle-keymap
	bindkey -M "$1" "[15~" zle-toggle-keymap
	bindkey -M "$1" "[17~" yank-x-selection
	bindkey -M "$1" "[18~" insert-x-selection
	bindkey -M "$1" "[" yank-x-selection
	bindkey -M "$1" "]" insert-x-selection
	# bindkey -M "$1" "[18~" append-x-selection
	# F9: Insert composed character
	# bindkey -M emacs "[19~" insert-composed-char

	bindkey -M "$1" ";" fzf-completion
	bindkey -M "$1" "\C-i" fasd-complete
	# bindkey -M "$1" "[Z" fzf-complete-f
	bindkey -M "$1" "[Z" fasd-complete-d
	bindkey -M "$1" "\C-i" "$fzf_default_completion"
	bindkey -M "$1" "i" fzf-locate-widget
	bindkey -M "$1" "r" fzf-history-widget
	bindkey -M "$1" "\C-t" transpose-words
	bindkey -M "$1" "t" fzf-file-widget
	## A Zsh Do What I Mean key. Attempts to predict what you will want to do next.
	## Usage: Type a command and hit control-u and zsh-dwim will attempt to transform your command.
	if zle -la | grep -q dwim; then
		bindkey -M "$1" "\C-u" dwim
		bindkey -M "$1" "[19~" dwim
	fi
} emacs vicmd viins

# more uglyness soz
#
# custom compdefs with generated and hardcoded arrays
() {
	local -a defargcmds asmcmds dbpkgs kmods pubkeys seckeys

	defargcmds+=(as auracle autopep8 autopep8-python2 basename bash bsdtar)
	defargcmds+=(calcc canto-curses canto-daemon canto-remote catdoc cd2raw)
	defargcmds+=(cdcd cdr2raw cdrdao cd-read cdu cepl cgasm chromium)
	defargcmds+=(col colordiff compton configure conky cower cpanm cppcheck)
	defargcmds+=(cpulimit crontab ctags curl define dmidecode elftoc)
	defargcmds+=(expac fasd file flac2all fusermount-glusterfs fusermount3)
	defargcmds+=(fzf gnome-keyring-daemon gpg-agent help2man highlight)
	defargcmds+=(highlight hping hsetroot install keyring kid3-cli)
	defargcmds+=(kid3-qt ld lighttpd2 ln lrz lua lz4 maim more mpd muttprint)
	defargcmds+=(mv named netstat netstat newsbeuter node nohup)
	defargcmds+=(objconv objdump optipng pacconf pactree paste pstree)
	defargcmds+=(qemu-img qemu-nbd reptyr resolvconf rfc rg rmdir)
	defargcmds+=(rmlint rst2man rst2man2 saldl scan-build seq shred)
	defargcmds+=(sox split stat st stjerm strings supybot swapon)
	defargcmds+=(systool termite test tic tload transmission-cli)
	defargcmds+=(transmission-create transmission-daemon transmission-edit)
	defargcmds+=(transmission-get transmission-gtk transmission-qt)
	defargcmds+=(transmission-remote transmission-remote-cli transmission-remote-cli)
	defargcmds+=(transmission-remote-gtk transmission-show transset-df)
	defargcmds+=(updatedb urxvtc urxvtcd urxvtd vanitygen vimpager x11vnc)
	defargcmds+=(xbindkeys xsel youtube-dl)

	asmcmds+=(${(o)$(cgasm -f '.*' | perl -alne '
			BEGIN{ my @cmds; }
			push @cmds, split(/ /, lc $F[0] =~ y|/| |r);
			END{ print join " ", @cmds;}'
		)})
	dbpkgs+=(${(fo@)$(pacman -Qq)})
	kmods+=(${${(f0@)$(find /usr/lib/modules/$(uname -r) -type f -name '*.ko.gz' 2>/dev/null)%.ko.gz}##*/})
	pubkeys+=(${${(Mo)$(gpg2 -k --no-default-keyring --list-options no-show-photos):%<*>}//(<|>)/})
	seckeys+=(${${(Mo)$(gpg2 -K --no-default-keyring --list-options no-show-photos):%<*>}//(<|>)/})

	cgasm_str+=$'_arguments "*:arg:_default" ":assembly instruction:('
	cgasm_str+="${asmcmds[*]}"
	cgasm_str+=')" -- '
	dgpg_str+=$'_arguments "*:arg:_default" ":secret keys:('
	# dgpg_str+=$'_arguments "*:arg:_default" ":public key:('
	dgpg_str+="${seckeys[*]}"
	# dgpg_str+="${pubkeys[*]}"
	dgpg_str+=$')" -- '
	hi_str+=$'_arguments "*:file:_files" ":syntax:_files '
	hi_str+=$'-W \'/usr/share/highlight/langDefs/\' '
	hi_str+=$'-g \'*.lang(:r)\'" -- '
	high_str+=$'_arguments "*:file:_files" ":theme:_files '
	high_str+=$'-W \'/usr/share/highlight/themes\''
	high_str+=$'-g \'*.theme(:r)\'" ":syntax:_files'
	high_str+=$'-W \'/usr/share/highlight/langDefs\''
	high_str+=$'-g \'*.lang(:r)\'" ":out format:'
	high_str+=$'(html xhtml latex tex rtf odt ansi xterm256 truecolor bbcode pango svg)" -- '
	pinfo_str+=$'_arguments "*:arg:_default" ":info page:_texinfo" -- '
	qpc_str+=$'_arguments "*:packages:('
	qpc_str+="${dbpkgs[*]}"
	qpc_str+=$')" -- '
	reptyr_str+=$'_arguments "*:arg:_default" ":processe:_pids" -- '
	modprobe_str+=$'_arguments "*:arg:_default" ":modules:('
	modprobe_str+="${kmods[*]}"
	modprobe_str+=$')" -- '

	() for 1 { compdef _gnu_generic "$1"; } $defargcmds

	compdef "$cgasm_str" cgasm
	compdef "$dgpg_str" dgpg
	compdef "$hi_str" hi
	compdef "$high_str" high
	compdef "$modprobe_str" modprobe
	compdef "$pinfo_str" pinfo
	compdef "$qpc_str" qpc
	compdef "$reptyr_str" reptyr
}

compdef _fman fman
compdef _gem gem
compdef _git fshow
compdef _man cppman
compdef _man tldr
compdef _pacaur apacman
compdef _pacaur pml
compdef _pacaur pspc
compdef _systemctl_status scrs
compdef _systemctl_status pscrs
compdef _systemctl_status uscrs
compdef _systemctl_status puscrs
compdef _texinfo info
compdef _uscrs uscrs
compdef _vim v
compdef _pip pip
compdef _au au
compdef _au wau
compdef _pwns pwns
compdef azle=autoload
compdef gnpm=npm
compdef p=perl
compdef run=gcc
compdef xs=xsel

# named directories
hash -d audio="/media/microSDXC/audio"
hash -d b="${HOME}/bin/"
hash -d aur="${HOME}/code/aur"
hash -d calibre="/media/microSDXC/calibre"
hash -d code="${P:-/store/code/projects}/school"
hash -d c="${CONF:-/store/dotfiles}"
hash -d djzomg="/media/microSDXC/Music/djzomg"
hash -d d="${CONF:-/store/dotfiles}/docs"
hash -d efi="/boot/efi/EFI"
hash -d euler="${HOME}/code/euler"
hash -d g="${HOME}/git"
hash -d inc="/usr/include"
hash -d initcpio="/usr/lib/initcpio/install"
hash -d magnets="${CONF:-/store/dotfiles}/magnets"
hash -d man="${CONF:-/store/dotfiles}/man"
hash -d music="/store/music"
hash -d nginx="/etc/nginx"
hash -d omz="/usr/share/oh-my-zsh"
hash -d plugins="/usr/share/oh-my-zsh/plugins"
hash -d p="${P:-/store/code/projects}"
hash -d prose="/store/writing"
hash -d repos="/store/repos"
hash -d rfc="/usr/share/doc/rfc"
hash -d s="/media/microSDXC/school"
hash -d surfraw="/usr/lib/surfraw"
hash -d stuff="/media/toshiba1TB"
hash -d systemd="/etc/systemd/system"
hash -d t="/store/torrents"
hash -d tt="/media/toshiba1TB/torrents"
hash -d vim="${HOME}/.vim"
hash -d wanderlust="/hdd/wanderlust"
hash -d words="${CONF:-/store/dotfiles}/unixstories"
hash -d www="/srv/http"
hash -d z="${ZDOTDIR:-$HOME/.zsh.d}"
hash -d zf="${ZDOTDIR:-$HOME/.zsh.d}/zfunctions"
hash -d zc="${ZDOTDIR:-$HOME/.zsh.d}/completions"
hash -d zp="${ZDOTDIR:-$HOME/.zsh.d}/plugins"
hash -d znc="/var/lib/znc/.znc/moddata/log/alyptik/freenode/"
hash -d zsh="$ZSH"

# Define word separators (for stuff like backward-word, forward-word, backward-kill-word,..)
WORDCHARS=
# WORDCHARS='_-*~'
# WORDCHARS='*?_-.[]~=/&;!#$%^ (){}<>'

# Completion tweaks
zstyle ':completion:*:(ssh|scp|sftp|rsync):*'		hosts \
	${${(Mu)${${${${(f@)$(cat ${HOME}/.ssh/{config,known_hosts})}%%,*}##*/}##*@}##*.*}%%:*}
	# ${(Mu)${${(f@)$(<${HOME}/.ssh/known_hosts)}%%,*}%%*.*}
zstyle ':acceptline'					nocompwarn true
# allow one error for every two characters typed in approximate completer
zstyle ':completion:*:approximate:'			max-errors 'reply=("$(( ($#PREFIX+$#SUFFIX)/2 ))" numeric)'
# zstyle ':completion:*:approximate:'			max-errors 5 numeric
# don't complete backup files as executables
zstyle ':completion:*:complete:-command-::commands'	ignored-patterns '(aptitude-*|*\~)'
# start menu completion only if it could find no unambiguous initial string
zstyle ':completion:*:correct:*'			insert-unambiguous true
zstyle ':completion:*:corrections'			format $'%{[0;31m%}%d (errors: %e)%{[0m%}'
zstyle ':completion:*:correct:*'			original true
# activate color-completion
zstyle ':completion:*:default'				list-colors "${(s.:.)LS_COLORS}"
# format on completion
zstyle ':completion:*:descriptions'			format $'%{[0;31m%}completing %B%d%b%{[0m%}'
# complete 'cd -<tab>' with menu
zstyle ':completion:*:*:cd:*:directory-stack'		menu yes select
# insert all expansions for expand completer
zstyle ':completion:*:expand:*'				tag-order all-expansions
zstyle ':completion:*:history-words'			list true
# activate menu
zstyle ':completion:*:history-words'			menu yes select
# ignore duplicate entries
zstyle ':completion:*:history-words'			remove-all-dups yes
zstyle ':completion:*:history-words'			stop yes
# match uppercase from lowercase
# zstyle ':completion:*'				matcher-list 'm:{a-z}={A-Z}'
# zstyle ':completion:*'				matcher-list 'm:{a-zA-Z}={A-Za-z}'
# 0 -- vanilla completion (abc => abc)
# 1 -- smart case completion (abc => Abc)
# 2 -- word flex completion (abc => A-big-Car)
# 3 -- full flex completion (abc => ABraCadabra)
zstyle ':completion:*'					matcher-list \
	'' \
	'm:{a-z\-}={A-Z\_}' \
	'r:[^[:alpha:]]||[[:alpha:]]=** r:|=* m:{a-z\-}={A-Z\_}' \
	'r:|?=** m:{a-z\-}={A-Z\_}'
# separate matches into groups
zstyle ':completion:*:matches'				group 'yes'
zstyle ':completion:*'					group-name ''
zstyle ':completion:*'					menu select
zstyle ':completion:*:messages'				format '%d'
zstyle ':completion:*:options'				auto-description '%d'
# describe options in full
zstyle ':completion:*:options'				description 'yes'
# on processes completion complete all user processes
zstyle ':completion:*:processes'			command 'ps -au$USER'
# offer indexes before parameters in subscripts
zstyle ':completion:*:*:-subscript-:*'			tag-order indexes parameters
# provide verbose completion information
zstyle ':completion:*'					verbose true
# recent (as of Dec 2007) zsh versions are able to provide descriptions
# for commands (read: 1st word in the line) that it will list for the user
# to choose from. The following disables that, because it's not exactly fast.
zstyle ':completion:*:-command-:*:'			verbose true
# set format for warnings
zstyle ':completion:*:warnings'				format $'%{[0;31m%}No matches for:%{[0m%} %d'
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
zstyle ':completion:*:manuals*'				insert-sections   true
zstyle ':completion:*:man*'				menu yes select
# provide .. as a completion
# zstyle ':completion:*'					special-dirs ..

# run rehash on completion so new installed program are found automatically:
_force_rehash() {
	(( CURRENT == 1 )) && rehash
	return 1
}

# correction
# try to be smart about when to use what completer...
zstyle -e ':completion:*'				completer '
	if [[ $_last_try != "$HISTNO$BUFFER$CURSOR" ]] ; then
		_last_try="$HISTNO$BUFFER$CURSOR"
		reply=(_complete _correct _approximate _expand _match _ignored _prefix _files)
	else
		if [[ $words[1] == (rm|mv|cp) ]] ; then
			reply=(_complete _files)
		else
			reply=(_oldlist _expand _force_rehash _complete _ignored _correct _approximate _files)
		fi
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

# cleanup
kill -USR1 $$

# end of .zshrc config
#
# all dankness must come to an end :(

bashcompinit() {
#autoload

_bash_complete() {
  local ret=1
  local -a suf matches
  local -x COMP_POINT COMP_CWORD
  local -a COMP_WORDS COMPREPLY BASH_VERSINFO
  local -x COMP_LINE="$words"
  local -A savejobstates savejobtexts

  (( COMP_POINT = 1 + ${#${(j. .)words[1,CURRENT]}} + $#QIPREFIX + $#IPREFIX + $#PREFIX ))
  (( COMP_CWORD = CURRENT - 1))
  COMP_WORDS=( $words )
  BASH_VERSINFO=( 2 05b 0 1 release )

  savejobstates=( ${(kv)jobstates} )
  savejobtexts=( ${(kv)jobtexts} )

  [[ ${argv[${argv[(I)nospace]:-0}-1]} = -o ]] && suf=( -S '' )

  matches=( ${(f)"$(compgen $@ -- ${words[CURRENT]})"} )

  if [[ -n $matches ]]; then
    if [[ ${argv[${argv[(I)filenames]:-0}-1]} = -o ]]; then
      compset -P '*/' && matches=( ${matches##*/} )
      compset -S '/*' && matches=( ${matches%%/*} )
      compadd -Q -f "${suf[@]}" -a matches && ret=0
    else
      compadd -Q "${suf[@]}" -a matches && ret=0
    fi
  fi

  if (( ret )); then
    if [[ ${argv[${argv[(I)default]:-0}-1]} = -o ]]; then
      _default "${suf[@]}" && ret=0
    elif [[ ${argv[${argv[(I)dirnames]:-0}-1]} = -o ]]; then
      _directories "${suf[@]}" && ret=0
    fi
  fi

  return ret
}

compgen() {
  local opts prefix suffix job OPTARG OPTIND ret=1
  local -a name res results jids
  local -A shortopts

  # words changes behavior: words[1] -> words[0]
  emulate -L sh
  setopt kshglob noshglob braceexpand nokshautoload

  shortopts=(
    a alias b builtin c command d directory e export f file
    g group j job k keyword u user v variable
  )

  while getopts "o:A:G:C:F:P:S:W:X:abcdefgjkuv" name; do
    case $name in
      [abcdefgjkuv]) OPTARG="${shortopts[$name]}" ;&
      A)
        case $OPTARG in
	  alias) results+=( "${(k)aliases[@]}" ) ;;
	  arrayvar) results+=( "${(k@)parameters[(R)array*]}" ) ;;
	  binding) results+=( "${(k)widgets[@]}" ) ;;
	  builtin) results+=( "${(k)builtins[@]}" "${(k)dis_builtins[@]}" ) ;;
	  command)
	    results+=(
	      "${(k)commands[@]}" "${(k)aliases[@]}" "${(k)builtins[@]}"
	      "${(k)functions[@]}" "${(k)reswords[@]}"
	    )
	  ;;
	  directory)
	    setopt bareglobqual
	    results+=( ${IPREFIX}${PREFIX}*${SUFFIX}${ISUFFIX}(N-/) )
	    setopt nobareglobqual
	  ;;
	  disabled) results+=( "${(k)dis_builtins[@]}" ) ;;
	  enabled) results+=( "${(k)builtins[@]}" ) ;;
	  export) results+=( "${(k)parameters[(R)*export*]}" ) ;;
	  file)
	    setopt bareglobqual
	    results+=( ${IPREFIX}${PREFIX}*${SUFFIX}${ISUFFIX}(N) )
	    setopt nobareglobqual
	  ;;
	  function) results+=( "${(k)functions[@]}" ) ;;
	  group)
	    emulate zsh
	    _groups -U -O res
	    emulate sh
	    setopt kshglob noshglob braceexpand
	    results+=( "${res[@]}" )
	  ;;
	  hostname)
	    emulate zsh
	    _hosts -U -O res
	    emulate sh
	    setopt kshglob noshglob braceexpand
	    results+=( "${res[@]}" )
	  ;;
	  job) results+=( "${savejobtexts[@]%% *}" );;
	  keyword) results+=( "${(k)reswords[@]}" ) ;;
	  running)
	    jids=( "${(@k)savejobstates[(R)running*]}" )
	    for job in "${jids[@]}"; do
	      results+=( ${savejobtexts[$job]%% *} )
	    done
	  ;;
	  stopped)
	    jids=( "${(@k)savejobstates[(R)suspended*]}" )
	    for job in "${jids[@]}"; do
	      results+=( ${savejobtexts[$job]%% *} )
	    done
	  ;;
	  setopt|shopt) results+=( "${(k)options[@]}" ) ;;
	  signal) results+=( "SIG${^signals[@]}" ) ;;
	  user) results+=( "${(k)userdirs[@]}" ) ;;
      	  variable) results+=( "${(k)parameters[@]}" ) ;;
	  helptopic) ;;
	esac
      ;;
      F)
        COMPREPLY=()
        local -a args
        args=( "${words[0]}" "${@[-1]}" "${words[CURRENT-2]}" )
        (){
          # There may be more things we need to add to this typeset to
          # protect bash functions from compsys special variable names
          typeset -h words
          $OPTARG "${args[@]}"
        }
	results+=( "${COMPREPLY[@]}" )
      ;;
      G)
        setopt nullglob
        results+=( ${~OPTARG} )
	unsetopt nullglob
      ;;
      W) results+=( ${(Q)~=OPTARG} ) ;;
      C) results+=( $(eval $OPTARG) ) ;;
      P) prefix="$OPTARG" ;;
      S) suffix="$OPTARG" ;;
      X)
        if [[ ${OPTARG[0]} = '!' ]]; then
	  results=( "${(M)results[@]:#${OPTARG#?}}" )
	else
 	  results=( "${results[@]:#$OPTARG}" )
	fi
      ;;
    esac
  done
  
  # support for the last, `word' option to compgen. Zsh's matching does a
  # better job but if you need to, comment this in and use compadd -U
  # (( $# >= OPTIND)) && results=( "${(M)results[@]:#${@[-1]}*}" )

  print -l -r -- "$prefix${^results[@]}$suffix"
}

complete() {
  emulate -L zsh
  local args void cmd print remove
  args=( "$@" )
  zparseopts -D -a void o: A: G: W: C: F: P: S: X: a b c d e f g j k u v \
      p=print r=remove
  if [[ -n $print ]]; then
    printf 'complete %2$s %1$s\n' "${(@kv)_comps[(R)_bash*]#* }"
  elif [[ -n $remove ]]; then
    for cmd; do
      unset "_comps[$cmd]"
    done
  else
    compdef _bash_complete\ ${(j. .)${(q)args[1,-1-$#]}} "$@"
  fi
}

unfunction bashcompinit
autoload -Uz bashcompinit
return 0
}

colors() {
# Put standard ANSI color codes in shell parameters for easy use.
# Note that some terminals do not support all combinations.

emulate -L zsh

typeset -Ag color colour

color=(
# Codes listed in this array are from ECMA-48, Section 8.3.117, p. 61.
# Those that are commented out are not widely supported or aren't closely
# enough related to color manipulation, but are included for completeness.

# Attribute codes:
  00 none                 # 20 gothic
  01 bold                 # 21 double-underline
  02 faint                  22 normal
  03 standout               23 no-standout
  04 underline              24 no-underline
  05 blink                  25 no-blink
# 06 fast-blink           # 26 proportional
  07 reverse                27 no-reverse
  08 conceal                28 no-conceal
# 09 strikethrough        # 29 no-strikethrough

# Font selection:
# 10 font-default
# 11 font-first
# 12 font-second
# 13 font-third
# 14 font-fourth
# 15 font-fifth
# 16 font-sixth
# 17 font-seventh
# 18 font-eighth
# 19 font-ninth

# Text color codes:
  30 black                  40 bg-black
  31 red                    41 bg-red
  32 green                  42 bg-green
  33 yellow                 43 bg-yellow
  34 blue                   44 bg-blue
  35 magenta                45 bg-magenta
  36 cyan                   46 bg-cyan
  37 white                  47 bg-white
# 38 iso-8316-6           # 48 bg-iso-8316-6
  39 default                49 bg-default

# Other codes:
# 50 no-proportional
# 51 border-rectangle
# 52 border-circle
# 53 overline
# 54 no-border
# 55 no-overline
# 56 through 59 reserved

# Ideogram markings:
# 60 underline-or-right
# 61 double-underline-or-right
# 62 overline-or-left
# 63 double-overline-or-left
# 64 stress
# 65 no-ideogram-marking
)

# A word about black and white:  The "normal" shade of white is really a
# very pale grey on many terminals; to get truly white text, you have to
# use bold white, and to get a truly white background you have to use
# bold reverse white bg-xxx where xxx is your desired foreground color
# (and which means the foreground is also bold).

# Map in both directions; could do this with e.g. ${(k)colors[(i)normal]},
# but it's clearer to include them all both ways.

local k
for k in ${(k)color}; do color[${color[$k]}]=$k; done

# Add "fg-" keys for all the text colors, for clarity.

for k in ${color[(I)3?]}; do color[fg-${color[$k]}]=$k; done

# This is inaccurate, but the prompt theme system needs it.

color[grey]=${color[black]}
color[fg-grey]=${color[grey]}
color[bg-grey]=${color[bg-black]}

# Assistance for the color-blind.

colour=(${(kv)color})	# A case where ksh namerefs would be useful ...

# The following are terminal escape sequences used by colored prompt themes.

local lc=$'\e[' rc=m	# Standard ANSI terminal escape values

typeset -Hg reset_color bold_color
reset_color="$lc${color[none]}$rc"
bold_color="$lc${color[bold]}$rc"

# Foreground

typeset -AHg fg fg_bold fg_no_bold
for k in ${(k)color[(I)fg-*]}; do
    fg[${k#fg-}]="$lc${color[$k]}$rc"
    fg_bold[${k#fg-}]="$lc${color[bold]};${color[$k]}$rc"
    fg_no_bold[${k#fg-}]="$lc${color[normal]};${color[$k]}$rc"
done

# Background

typeset -AHg bg bg_bold bg_no_bold
for k in ${(k)color[(I)bg-*]}; do
    bg[${k#bg-}]="$lc${color[$k]}$rc"
    bg_bold[${k#bg-}]="$lc${color[bold]};${color[$k]}$rc"
    bg_no_bold[${k#bg-}]="$lc${color[normal]};${color[$k]}$rc"
done
}

compinit() {
# Initialisation for new style completion. This mainly contains some helper
# functions and setup. Everything else is split into different files that
# will automatically be made autoloaded (see the end of this file).  The
# names of the files that will be considered for autoloading are those that
# begin with an underscores (like `_condition).
#
# The first line of each of these files is read and must indicate what
# should be done with its contents:
#
#   `#compdef <names ...>'
#     If the first line looks like this, the file is autoloaded as a
#     function and that function will be called to generate the matches
#     when completing for one of the commands whose <names> are given.
#     The names may also be interspersed with `-T <assoc>' options
#     specifying for which set of functions this should be added.
#
#   `#compdef -[pP] <patterns ...>'
#     This defines a function that should be called to generate matches
#     for commands whose name matches <pattern>. Note that only one pattern
#     may be given.
#
#   `#compdef -k <style> [ <key-sequence> ... ]'
#     This is used to bind special completions to all the given
#     <key-sequence>(s). The <style> is the name of one of the built-in
#     completion widgets (complete-word, delete-char-or-list,
#     expand-or-complete, expand-or-complete-prefix, list-choices,
#     menu-complete, menu-expand-or-complete, or reverse-menu-complete).
#     This creates a widget behaving like <style> so that the
#     completions are chosen as given in the rest of the file,
#     rather than by the context.  The widget has the same name as
#     the autoload file and can be bound using bindkey in the normal way.
#
#   `#compdef -K <widget-name> <style> <key-sequence> [ ... ]'
#     This is similar to -k, except it takes any number of sets of
#     three arguments.  In each set, the widget <widget-name> will
#     be defined, which will behave as <style>, as with -k, and will
#     be bound to <key-sequence>, exactly one of which must be defined.
#     <widget-name> must be different for each:  this must begin with an
#     underscore, else one will be added, and should not clash with other
#     completion widgets (names based on the name of the function are the
#     clearest), but is otherwise arbitrary.  It can be tested in the
#     function by the parameter $WIDGET.
#
#   `#autoload [ <options> ]'
#     This is for helper functions that are not used to
#     generate matches, but should automatically be loaded
#     when they are called. The <options> will be given to the
#     autoload builtin when making the function autoloaded. Note
#     that this need not include `-U' and `-z'.
#
# Note that no white space is allowed between the `#' and the rest of
# the string.
#
# Functions that are used to generate matches should return zero if they
# were able to add matches and non-zero otherwise.
#
# See the file `compdump' for how to speed up initialisation.

# If we got the `-d'-flag, we will automatically dump the new state (at
# the end).  This takes the dumpfile as an argument.  -d (with the
# default dumpfile) is now the default; to turn off dumping use -D.

# The -C flag bypasses both the check for rebuilding the dump file and the
# usual call to compaudit; the -i flag causes insecure directories found by
# compaudit to be ignored, and the -u flag causes all directories found by
# compaudit to be used (without security checking).  Otherwise the user is
# queried for whether to use or ignore the insecure directories (which
# means compinit should not be called from non-interactive shells).

emulate -L zsh
setopt extendedglob

typeset _i_dumpfile _i_files _i_line _i_done _i_dir _i_autodump=1
typeset _i_tag _i_file _i_addfiles _i_fail=ask _i_check=yes _i_name

while [[ $# -gt 0 && $1 = -[dDiuC] ]]; do
  case "$1" in
  -d)
    _i_autodump=1
    shift
    if [[ $# -gt 0 && "$1" != -[dfQC] ]]; then
      _i_dumpfile="$1"
      shift
    fi
    ;;
  -D)
    _i_autodump=0
    shift
    ;;
  -i)
    _i_fail=ign
    shift
    ;;
  -u)
    _i_fail=use
    shift
    ;;
  -C)
    _i_check=
    shift
    ;;
  esac
done

# The associative arrays containing the definitions for the commands and
# services.

typeset -gHA _comps _services _patcomps _postpatcomps

# `_compautos' contains the names and options for autoloaded functions
# that get options.

typeset -gHA _compautos

# The associative array use to report information about the last
# completion to the outside.

typeset -gHA _lastcomp

# Remember dumpfile.
if [[ -n $_i_dumpfile ]]; then
  # Explicitly supplied dumpfile.
  typeset -g _comp_dumpfile="$_i_dumpfile"
else
  typeset -g _comp_dumpfile="${ZDOTDIR:-$HOME}/.zcompdump"
fi

# The standard options set in completion functions.

typeset -gHa _comp_options
_comp_options=(
       bareglobqual
       extendedglob
       glob
       multibyte
       multifuncdef
       nullglob
       rcexpandparam
       unset
    NO_allexport
    NO_aliases
    NO_cshnullglob
    NO_cshjunkiequotes
    NO_errexit
    NO_errreturn
    NO_globassign
    NO_globsubst
    NO_histsubstpattern
    NO_ignorebraces
    NO_ignoreclosebraces
    NO_kshglob
    NO_ksharrays
    NO_kshtypeset
    NO_markdirs
    NO_octalzeroes
    NO_posixbuiltins
    NO_posixidentifiers
    NO_shwordsplit
    NO_shglob
    NO_warnnestedvar
    NO_warncreateglobal
)

# And this one should be `eval'ed at the beginning of every entry point
# to the completion system.  It sets up what we currently consider a
# sane environment.  That means we set the options above, make sure we
# have a valid stdin descriptor (zle closes it before calling widgets)
# and don't get confused by user's ZERR trap handlers.

typeset -gH _comp_setup='local -A _comp_caller_options;
             _comp_caller_options=(${(kv)options[@]});
             setopt localoptions localtraps localpatterns ${_comp_options[@]};
             local IFS=$'\'\ \\t\\r\\n\\0\'';
             builtin enable -p \| \~ \( \? \* \[ \< \^ \# 2>&-;
             exec </dev/null;
             trap - ZERR;
             local -a reply;
             local REPLY'

# These can hold names of functions that are to be called before/after all
# matches have been generated.

typeset -ga compprefuncs comppostfuncs
compprefuncs=()
comppostfuncs=()

# Loading it now ensures that the `funcstack' parameter is always correct.

: $funcstack

# This function is used to register or delete completion functions. For
# registering completion functions, it is invoked with the name of the
# function as it's first argument (after the options). The other
# arguments depend on what type of completion function is defined. If
# none of the `-p' and `-k' options is given a function for a command is
# defined. The arguments after the function name are then interpreted as
# the names of the command for which the function generates matches.
# With the `-p' option a function for a name pattern is defined. This 
# function will be invoked when completing for a command whose name 
# matches the pattern given as argument after the function name (in this
# case only one argument is accepted).
# The option `-P' is like `-p', but the function will be called after
# trying to find a function defined for the command on the line if no
# such function could be found.
# With the `-k' option a function for a special completion keys is 
# defined and immediately bound to those keys. Here, the extra arguments
# are the name of one of the builtin completion widgets and any number
# of key specifications as accepted by the `bindkey' builtin.
# In any case the `-a' option may be given which makes the function
# whose name is given as the first argument be autoloaded. When defining
# a function for command names the `-n' option may be given and keeps
# the definitions from overriding any previous definitions for the
# commands; with `-k', the `-n' option prevents compdef from rebinding
# a key sequence which is already bound.
# For deleting definitions, the `-d' option must be given. Without the
# `-p' option, this deletes definitions for functions for the commands
# whose names are given as arguments. If combined with the `-p' option
# it deletes the definitions for the patterns given as argument.
# The `-d' option may not be combined with the `-k' option, i.e.
# definitions for key function can not be removed.
#
# Examples:
#
#  compdef -a foo bar baz
#    make the completion for the commands `bar' and `baz' use the
#    function `foo' and make this function be autoloaded
#
#  compdef -p foo 'c*'
#    make completion for all command whose name begins with a `c'
#    generate matches by calling the function `foo' before generating
#    matches defined for the command itself
#
#  compdef -k foo list-choices '^X^M' '\C-xm'
#    make the function `foo' be invoked when typing `Control-X Control-M'
#    or `Control-X m'; the function should generate matches and will
#    behave like the `list-choices' builtin widget
#
#  compdef -d bar baz
#   delete the definitions for the command names `bar' and `baz'

compdef() {
  local opt autol type func delete eval new i ret=0 cmd svc
  local -a match mbegin mend

  emulate -L zsh
  setopt extendedglob

  # Get the options.

  if (( ! $# )); then
    print -u2 "$0: I need arguments"
    return 1
  fi

  while getopts "anpPkKde" opt; do
    case "$opt" in
    a)    autol=yes;;
    n)    new=yes;;
    [pPkK]) if [[ -n "$type" ]]; then
            # Error if both `-p' and `-k' are given (or one of them
	    # twice).
            print -u2 "$0: type already set to $type"
	    return 1
	  fi
	  if [[ "$opt" = p ]]; then
	    type=pattern
	  elif [[ "$opt" = P ]]; then
	    type=postpattern
	  elif [[ "$opt" = K ]]; then
	    type=widgetkey
	  else
	    type=key
	  fi
	  ;;
    d) delete=yes;;
    e) eval=yes;;
    esac
  done
  shift OPTIND-1

  if (( ! $# )); then
    print -u2 "$0: I need arguments"
    return 1
  fi

  if [[ -z "$delete" ]]; then
    # If the first word contains an equal sign, all words must contain one
    # and we define which services to use for the commands.

    if [[ -z "$eval" ]] && [[ "$1" = *\=* ]]; then
      while (( $# )); do
        if [[ "$1" = *\=* ]]; then
	  cmd="${1%%\=*}"
	  svc="${1#*\=}"
          func="$_comps[${_services[(r)$svc]:-$svc}]"
          [[ -n ${_services[$svc]} ]] &&
              svc=${_services[$svc]}
	  [[ -z "$func" ]] &&
	      func="${${_patcomps[(K)$svc][1]}:-${_postpatcomps[(K)$svc][1]}}"
          if [[ -n "$func" ]]; then
	    _comps[$cmd]="$func"
	    _services[$cmd]="$svc"
	  else
	    print -u2 "$0: unknown command or service: $svc"
	    ret=1
	  fi
	else
	  print -u2 "$0: invalid argument: $1"
	  ret=1
	fi
        shift
      done

      return ret
    fi

    # Adding definitions, first get the name of the function name
    # and probably do autoloading.

    func="$1"
    [[ -n "$autol" ]] && autoload -Uz "$func"
    shift

    case "$type" in
    widgetkey)
      while [[ -n $1 ]]; do
	if [[ $# -lt 3 ]]; then
	  print -u2 "$0: compdef -K requires <widget> <comp-widget> <key>"
	  return 1
	fi
	[[ $1 = _* ]] || 1="_$1"
	[[ $2 = .* ]] || 2=".$2"
        [[ $2 = .menu-select ]] && zmodload -i zsh/complist
	zle -C "$1" "$2" "$func"
	if [[ -n $new ]]; then
	  bindkey "$3" | IFS=$' \t' read -A opt
	  [[ $opt[-1] = undefined-key ]] && bindkey "$3" "$1"
	else
	  bindkey "$3" "$1"
	fi
	shift 3
      done
      ;;
    key)
      if [[ $# -lt 2 ]]; then
        print -u2 "$0: missing keys"
	return 1
      fi

      # Define the widget.
      if [[ $1 = .* ]]; then
        [[ $1 = .menu-select ]] && zmodload -i zsh/complist
	zle -C "$func" "$1" "$func"
      else
        [[ $1 = menu-select ]] && zmodload -i zsh/complist
	zle -C "$func" ".$1" "$func"
      fi
      shift

      # And bind the keys...
      for i; do
        if [[ -n $new ]]; then
	   bindkey "$i" | IFS=$' \t' read -A opt
	   [[ $opt[-1] = undefined-key ]] || continue
	fi
        bindkey "$i" "$func"
      done
      ;;
    *)
      # For commands store the function name in the
      # associative array, command names as keys.
      while (( $# )); do
        if [[ "$1" = -N ]]; then
          type=normal
        elif [[ "$1" = -p ]]; then
          type=pattern
        elif [[ "$1" = -P ]]; then
          type=postpattern
        else
          case "$type" in
          pattern)
	    if [[ $1 = (#b)(*)=(*) ]]; then
	      _patcomps[$match[1]]="=$match[2]=$func"
	    else
	      _patcomps[$1]="$func"
	    fi
            ;;
          postpattern)
	    if [[ $1 = (#b)(*)=(*) ]]; then
	      _postpatcomps[$match[1]]="=$match[2]=$func"
	    else
	      _postpatcomps[$1]="$func"
	    fi
            ;;
          *)
            if [[ "$1" = *\=* ]]; then
	      cmd="${1%%\=*}"
	      svc=yes
            else
	      cmd="$1"
	      svc=
            fi
            if [[ -z "$new" || -z "${_comps[$1]}" ]]; then
              _comps[$cmd]="$func"
	      [[ -n "$svc" ]] && _services[$cmd]="${1#*\=}"
	    fi
            ;;
          esac
        fi
        shift
      done
      ;;
    esac
  else
    # Handle the `-d' option, deleting.

    case "$type" in
    pattern)
      unset "_patcomps[$^@]"
      ;;
    postpattern)
      unset "_postpatcomps[$^@]"
      ;;
    key)
      # Oops, cannot do that yet.

      print -u2 "$0: cannot restore key bindings"
      return 1
      ;;
    *)
      unset "_comps[$^@]"
    esac
  fi
}

# Now we automatically make the definition files autoloaded.

typeset _i_wdirs _i_wfiles

_i_wdirs=()
_i_wfiles=()

autoload -Uz compaudit
if [[ -n "$_i_check" ]]; then
  typeset _i_q
  if ! eval compaudit; then
    if [[ -n "$_i_q" ]]; then
      if [[ "$_i_fail" = ask ]]; then
        if ! read -q \
"?zsh compinit: insecure $_i_q, run compaudit for list.
Ignore insecure $_i_q and continue [y] or abort compinit [n]? "; then
	  print -u2 "$0: initialization aborted"
          unfunction compinit compdef
          unset _comp_dumpfile _comp_secure compprefuncs comppostfuncs \
                _comps _patcomps _postpatcomps _compautos _lastcomp

          return 1
        fi
        _i_wfiles=()
	_i_wdirs=()
      else
        (( $#_i_wfiles )) && _i_files=( "${(@)_i_files:#(${(j:|:)_i_wfiles%.zwc})}"  )
        (( $#_i_wdirs ))  && _i_files=( "${(@)_i_files:#(${(j:|:)_i_wdirs%.zwc})/*}" )
      fi
    fi
    typeset -g _comp_secure=yes
  fi
fi

# Make sure compdump is available, even if we aren't going to use it.
autoload -Uz compdump compinstall

# If we have a dump file, load it.

_i_done=''

if [[ -f "$_comp_dumpfile" ]]; then
  if [[ -n "$_i_check" ]]; then
    IFS=$' \t' read -rA _i_line < "$_comp_dumpfile"
    if [[ _i_autodump -eq 1 && $_i_line[2] -eq $#_i_files &&
        $ZSH_VERSION = $_i_line[4] ]]
    then
      builtin . "$_comp_dumpfile"
      _i_done=yes
    fi
  else
    builtin . "$_comp_dumpfile"
    _i_done=yes
  fi
fi
if [[ -z "$_i_done" ]]; then
  typeset -A _i_test

  for _i_dir in $fpath; do
    [[ $_i_dir = . ]] && continue
    (( $_i_wdirs[(I)$_i_dir] )) && continue
    for _i_file in $_i_dir/^([^_]*|*~|*.zwc)(N); do
      _i_name="${_i_file:t}"
      (( $+_i_test[$_i_name] + $_i_wfiles[(I)$_i_file] )) && continue
      _i_test[$_i_name]=yes
      IFS=$' \t' read -rA _i_line < $_i_file
      _i_tag=$_i_line[1]
      shift _i_line
      case $_i_tag in
      (\#compdef)
	if [[ $_i_line[1] = -[pPkK](n|) ]]; then
	  compdef ${_i_line[1]}na "${_i_name}" "${(@)_i_line[2,-1]}"
	else
	  compdef -na "${_i_name}" "${_i_line[@]}"
	fi
	;;
      (\#autoload)
	autoload -Uz "$_i_line[@]" ${_i_name}
	[[ "$_i_line" != \ # ]] && _compautos[${_i_name}]="$_i_line"
	;;
      esac
    done
  done

  # If autodumping was requested, do it now.

  if [[ $_i_autodump = 1 ]]; then
    compdump
  fi
fi

# Rebind the standard widgets
for _i_line in complete-word delete-char-or-list expand-or-complete \
  expand-or-complete-prefix list-choices menu-complete \
  menu-expand-or-complete reverse-menu-complete; do
  zle -C $_i_line .$_i_line _main_complete
done
zle -la menu-select && zle -C menu-select .menu-select _main_complete

# If the default completer set includes _expand, and tab is bound
# to expand-or-complete, rebind it to complete-word instead.
bindkey '^i' | IFS=$' \t' read -A _i_line
if [[ ${_i_line[2]} = expand-or-complete ]] &&
  zstyle -a ':completion:' completer _i_line &&
  (( ${_i_line[(i)_expand]} <= ${#_i_line} )); then
  bindkey '^i' complete-word
fi

unfunction compinit compaudit
autoload -Uz compinit compaudit

return 0
}

promptinit() {
##
## zsh prompt themes extension
## by Adam Spiers <adam@spiers.net>
##
## Load with `autoload -Uz promptinit; promptinit'.
## Type `prompt -h' for help.
##

typeset -gaU prompt_themes
typeset -ga prompt_theme
typeset -g prompt_newline
prompt_themes=()

promptinit () {
  emulate -L zsh
  setopt extendedglob
  local ppath='' name theme
  local -a match mbegin mend

  # Autoload all prompt_*_setup functions in fpath
  for theme in $^fpath/prompt_*_setup(N); do
    if [[ $theme == */prompt_(#b)(*)_setup ]]; then
      name="$match[1]"
      if [[ -r "$theme" ]]; then
        prompt_themes=($prompt_themes $name)
        autoload -Uz prompt_${name}_setup
      else
        print "Couldn't read file $theme containing theme $name."
      fi
    else
      print "Eh?  Mismatch between glob patterns in promptinit."
    fi
  done

  # To manipulate precmd and preexec hooks...
  autoload -Uz add-zsh-hook

  # Variables common to all prompt styles
  prompt_newline=$'\n%{\r%}'
}

prompt_preview_safely() {
  emulate -L zsh
  print -P "%b%f%k"
  if [[ -z "$prompt_themes[(r)$1]" ]]; then
    print "Unknown theme: $1"
    return
  fi

  # This handles all the stuff from the default :prompt-theme cleanup
  local +h PS1=$PS1 PS2=$PS2 PS3=$PS3 PS4=$PS4 RPS1=$RPS1 RPS2=$RPS2
  local +h PROMPT=$PROMPT RPROMPT=$RPOMPT RPROMPT2=$RPROMPT2 PSVAR=$PSVAR
  local -a precmd_functions preexec_functions prompt_preview_cleanup
  local -aLl +h zle_highlight

  {
    # Save and clear current restore-point if any
    zstyle -g prompt_preview_cleanup :prompt-theme cleanup
    {
      zstyle -d :prompt-theme cleanup

      # The next line is a bit ugly.  It (perhaps unnecessarily)
      # runs the prompt theme setup function to ensure that if
      # the theme has a _preview function that it's been autoloaded.
      prompt_${1}_setup

      if typeset +f prompt_${1}_preview >&/dev/null; then
        prompt_${1}_preview "$@[2,-1]"
      else
        prompt_preview_theme "$@"
      fi
    } always {
      # Run any theme-specific cleanup, then reset restore point
      zstyle -t :prompt-theme cleanup
    }
  } always {
    (( $#prompt_preview_cleanup )) &&
      zstyle -e :prompt-theme cleanup "${prompt_preview_cleanup[@]}"
  }
}

set_prompt() {
  emulate -L zsh
  local opt preview theme usage old_theme

  usage='Usage: prompt <options>
Options:
    -c              Show currently selected theme and parameters
    -l              List currently available prompt themes
    -p [<themes>]   Preview given themes (defaults to all)
    -h [<theme>]    Display help (for given theme)
    -s <theme>      Set and save theme
    <theme>         Switch to new theme immediately (changes not saved)

Use prompt -h <theme> for help on specific themes.'

  getopts "chlps:" opt
  case "$opt" in
    (h|p)
      setopt localtraps
      if [[ -z "$prompt_theme[1]" ]]; then
        # Not using a prompt theme; save settings
        local +h PS1=$PS1 PS2=$PS2 PS3=$PS3 PS4=$PS4 RPS1=$RPS1 RPS2=$RPS2
        local +h PROMPT=$PROMPT RPROMPT=$RPOMPT RPROMPT2=$RPROMPT2 PSVAR=$PSVAR
        local -a precmd_functions preexec_functions
      else
        trap 'prompt_${prompt_theme[1]}_setup "${(@)prompt_theme[2,-1]}"' 0
      fi
      ;;
  esac
  case "$opt" in
    c) if [[ -n $prompt_theme ]]; then
         print -n "Current prompt theme"
         (( $#prompt_theme > 1 )) && print -n " with parameters"
         print " is:\n  $prompt_theme"
       else
         print "Current prompt is not a theme."
       fi
       return
       ;;
    h) if [[ -n "$2" && -n $prompt_themes[(r)$2] ]]; then
         if functions prompt_$2_setup >/dev/null; then
           # The next line is a bit ugly.  It (perhaps unnecessarily)
           # runs the prompt theme setup function to ensure that if
           # the theme has a _help function that it's been autoloaded.
           prompt_$2_setup
         fi
         if functions prompt_$2_help >/dev/null; then
           print "Help for $2 theme:\n"
           prompt_$2_help
         else
           print "No help available for $2 theme."
         fi
         print "\nType \`prompt -p $2' to preview the theme, \`prompt $2'"
         print "to try it out, and \`prompt -s $2' to use it in future sessions."
       else
         print "$usage"
       fi
       ;;
    l) print Currently available prompt themes:
       print $prompt_themes
       return
       ;;
    p) preview=( $prompt_themes )
       (( $#* > 1 )) && preview=( "$@[2,-1]" )
       for theme in $preview; do
         [[ "$theme" == "$prompt_theme[*]" ]] && continue
         prompt_preview_safely "$=theme"
       done
       print -P "%b%f%k"
       ;;
    s) print "Set and save not yet implemented.  Please ensure your ~/.zshrc"
       print "contains something similar to the following:\n"
       print "  autoload -Uz promptinit"
       print "  promptinit"
       print "  prompt $*[2,-1]"
       shift
       ;&
    *) if [[ "$1" == 'random' ]]; then
         local random_themes
         if (( $#* == 1 )); then
           random_themes=( $prompt_themes )
         else
           random_themes=( "$@[2,-1]" )
         fi
         local i=$(( ( $RANDOM % $#random_themes ) + 1 ))
         argv=( "${=random_themes[$i]}" )
       fi
       if [[ -z "$1" || -z $prompt_themes[(r)$1] ]]; then
         print "$usage"
         return
       fi

       # Reset some commonly altered bits to the default
       local hook
       for hook in chpwd precmd preexec periodic zshaddhistory zshexit; do
         add-zsh-hook -D "${hook}" "prompt_*_${hook}"
       done
       typeset -ga zle_highlight=( ${zle_highlight:#default:*} )
       (( ${#zle_highlight} )) || unset zle_highlight

       prompt_$1_setup "$@[2,-1]" && prompt_theme=( "$@" )
       ;;
  esac
}

prompt_cleanup () {
  local -a cleanup_hooks
  if zstyle -g cleanup_hooks :prompt-theme cleanup
  then
    cleanup_hooks+=(';' "$@")
    zstyle -e :prompt-theme cleanup "${cleanup_hooks[@]}"
  elif (( $+prompt_preview_cleanup == 0 ))
  then
    print -u2 "prompt_cleanup: no prompt theme active"
    return 1
  fi
}

prompt () {
  local -a prompt_opts theme_active

  zstyle -g theme_active :prompt-theme cleanup || {
    # This is done here rather than in set_prompt so that it
    # is safe and sane for set_prompt to setopt localoptions,
    # which will be cleared before we arrive back here again.
    # This is also why we pass around the prompt_opts array.
    [[ -o promptbang ]] && prompt_opts+=(bang)
    [[ -o promptcr ]] && prompt_opts+=(cr)
    [[ -o promptpercent ]] && prompt_opts+=(percent)
    [[ -o promptsp ]] && prompt_opts+=(sp)
    [[ -o promptsubst ]] && prompt_opts+=(subst)
    zstyle -e :prompt-theme cleanup \
        'zstyle -d :prompt-theme cleanup;' \
	'prompt_default_setup;' \
        ${PS1+PS1="${(q)PS1}"} \
        ${PS2+PS2="${(q)PS2}"} \
        ${PS3+PS3="${(q)PS3}"} \
        ${PS4+PS4="${(q)PS4}"} \
        ${RPS1+RPS1="${(q)RPS1}"} \
        ${RPS2+RPS2="${(q)RPS2}"} \
        ${RPROMPT+RPROMPT="${(q)RPROMPT}"} \
        ${RPROMPT2+RPROMPT2="${(q)RPROMPT2}"} \
        ${PSVAR+PSVAR="${(q)PSVAR}"} \
        "precmd_functions=(${(q)precmd_functions[@]})" \
        "preexec_functions=(${(q)preexec_functions[@]})" \
        "prompt_opts=( ${prompt_opts[*]} )" \
        'reply=(yes)'
  }
  set_prompt "$@"

  (( ${#prompt_opts} )) &&
      setopt noprompt{bang,cr,percent,sp,subst} "prompt${^prompt_opts[@]}"

  true
}

prompt_preview_theme () {
  emulate -L zsh

  # Check for proper state handling
  (( $+prompt_preview_cleanup )) || {
    prompt_preview_safely "$@"
    return
  }

  # Minimal preview for prompts that don't supply one
  local -a prompt_opts
  print -n "$1 theme"
  (( $#* > 1 )) && print -n " with parameters \`$*[2,-1]'"
  print ":"
  prompt_${1}_setup "$@[2,-1]"
  (( ${#prompt_opts} )) &&
      setopt noprompt{bang,cr,percent,sp,subst} "prompt${^prompt_opts[@]}"
  [[ -n ${precmd_functions[(r)prompt_${1}_precmd]} ]] &&
    prompt_${1}_precmd
  [[ -o promptcr ]] && print -n $'\r'; :
  print -P "${PS1}command arg1 arg2 ... argn"
  [[ -n ${preexec_functions[(r)prompt_${1}_preexec]} ]] &&
    prompt_${1}_preexec
}

[[ -o kshautoload ]] || promptinit "$@"
}

_systemctl() {
#compdef systemctl

(( $+functions[_systemctl_command] )) || _systemctl_command()
{
  local -a _systemctl_cmds
  _systemctl_cmds=(
    "list-sockets:List sockets"
    "list-timers:List timers"
    "list-units:List units"
    "start:Start (activate) one or more units"
    "stop:Stop (deactivate) one or more units"
    "reload:Reload one or more units"
    "restart:Start or restart one or more units"
    "condrestart:Restart one or more units if active"
    "try-restart:Restart one or more units if active"
    "reload-or-restart:Reload one or more units if possible, otherwise start or restart"
    "force-reload:Reload one or more units if possible, otherwise restart if active"
    "hibernate:Hibernate the system"
    "hybrid-sleep:Hibernate and suspend the system"
    "try-reload-or-restart:Reload one or more units if possible, otherwise restart if active"
    "isolate:Start one unit and stop all others"
    "kill:Send signal to processes of a unit"
    "is-active:Check whether units are active"
    "is-failed:Check whether units are failed"
    "status:Show runtime status of one or more units"
    "show:Show properties of one or more units/jobs or the manager"
    "cat:Show the source unit files and drop-ins"
    "reset-failed:Reset failed state for all, one, or more units"
    "list-unit-files:List installed unit files"
    "enable:Enable one or more unit files"
    "disable:Disable one or more unit files"
    "add-wants:Add Wants= dependencies to a unit"
    "add-requires:Add Requires= dependencies to a unit"
    "reenable:Reenable one or more unit files"
    "preset:Enable/disable one or more unit files based on preset configuration"
    "set-default:Set the default target"
    "get-default:Query the default target"
    "edit:Edit one or more unit files"
    "is-system-running:Query overall status of the system"
    "help:Show documentation for specified units"
    "list-dependencies:Show unit dependency tree"
    "mask:Mask one or more units"
    "unmask:Unmask one or more units"
    "link:Link one or more units files into the search path"
    "is-enabled:Check whether unit files are enabled"
    "list-jobs:List jobs"
    "cancel:Cancel all, one, or more jobs"
    "show-environment:Dump environment"
    "set-environment:Set one or more environment variables"
    "unset-environment:Unset one or more environment variables"
    "daemon-reload:Reload systemd manager configuration"
    "daemon-reexec:Reexecute systemd manager"
    "default:Enter system default mode"
    "rescue:Enter system rescue mode"
    "emergency:Enter system emergency mode"
    "halt:Shut down and halt the system"
    "suspend:Suspend the system"
    "poweroff:Shut down and power-off the system"
    "reboot:Shut down and reboot the system"
    "kexec:Shut down and reboot the system with kexec"
    "exit:Ask for user instance termination"
    "switch-root:Change root directory"
    "revert:Revert unit files to their vendor versions"
  )

  if (( CURRENT == 1 )); then
    _describe -t commands 'systemctl command' _systemctl_cmds || compadd "$@"
  else
    local curcontext="$curcontext" expl

    cmd="${${_systemctl_cmds[(r)$words[1]:*]%%:*}}"
    # Deal with any aliases
    case $cmd in
      condrestart) cmd="try-restart";;
      force-reload) cmd="try-reload-or-restart";;
    esac

    if (( $#cmd )); then
      curcontext="${curcontext%:*:*}:systemctl-${cmd}:"

      local update_policy
      zstyle -s ":completion:${curcontext}:" cache-policy update_policy
      if [[ -z "$update_policy" ]]; then
        zstyle ":completion:${curcontext}:" cache-policy _systemctl_caching_policy
      fi

      _call_function ret _systemctl_$cmd || _message 'no more arguments'
    else
      _message "unknown systemctl command: $words[1]"
    fi
    return ret
  fi
}

__systemctl()
{
  systemctl $_sys_service_mgr --full --no-legend --no-pager "$@" 2>/dev/null
}


# Fills the unit list
_systemctl_all_units()
{
  if ( [[ ${+_sys_all_units} -eq 0 ]] || _cache_invalid SYS_ALL_UNITS$_sys_service_mgr ) ||
    ! _retrieve_cache SYS_ALL_UNITS$_sys_service_mgr;
  then
    _sys_all_units=( ${${(f)"$(__systemctl list-units --all)"}%% *} )
    _store_cache SYS_ALL_UNITS$_sys_service_mgr _sys_all_units
  fi
}

# Fills the unit list including all file units
_systemctl_really_all_units()
{
  local -a all_unit_files;
  local -a really_all_units;
  if ( [[ ${+_sys_really_all_units} -eq 0 ]] || _cache_invalid SYS_REALLY_ALL_UNITS$_sys_service_mgr ) ||
    ! _retrieve_cache SYS_REALLY_ALL_UNITS$_sys_service_mgr;
  then
    all_unit_files=( ${${(f)"$(__systemctl list-unit-files)"}%% *} )
    _systemctl_all_units
    really_all_units=($_sys_all_units $all_unit_files)
    _sys_really_all_units=(${(u)really_all_units})
    _store_cache SYS_REALLY_ALL_UNITS$_sys_service_mgr _sys_really_all_units
  fi
}

_filter_units_by_property() {
  local property=$1 value=$2; shift 2
  local -a units; units=("${(q-)@}")
  local -A props
  props=(${(f)"$(_call_program units "$service $_sys_service_mgr show --no-pager --property=\"Id,$property\" -- ${units} 2>/dev/null")"})
  echo -E - "${(@g:o:)${(k@)props[(Re)$property=$value]}#Id=}"
}

_systemctl_get_template_names() { echo -E - ${^${(M)${(f)"$(__systemctl list-unit-files "*$PREFIX*$SUFFIX*" )"}##*@.[^[:space:]]##}%%@.*}\@ }


_systemctl_active_units()  {_sys_active_units=(  ${${(f)"$(__systemctl list-units "*$PREFIX*$SUFFIX*" )"}%% *} )}

_systemctl_startable_units(){
    _sys_startable_units=( $( _filter_units_by_property ActiveState inactive $(
                          _filter_units_by_property CanStart yes $(
                          __systemctl $mode list-unit-files --state enabled,disabled,static "*$PREFIX*$SUFFIX*" | \
                               { while read -r a b; do [[ $a =~ @\. ]] || echo -E - " $a"; done; }
                          __systemctl $mode list-units --state inactive,failed "*$PREFIX*$SUFFIX*" | \
                               { while read -r a b; do echo -E - " $a"; done; } )) ) )
}

_systemctl_restartable_units(){
    _sys_restartable_units=( $(_filter_units_by_property CanStart yes $(
                          __systemctl $mode list-unit-files --state enabled,disabled,static "*$PREFIX*$SUFFIX*" | \
                               { while read -r a b; do [[ $a =~ @\. ]] || echo -E - " $a"; done; }
                          __systemctl $mode list-units "*$PREFIX*$SUFFIX*" | \
                               { while read -r a b; do echo -E - " $a"; done; } )) )
}

_systemctl_failed_units()  {_sys_failed_units=( ${${(f)"$(__systemctl list-units --state=failed "*$PREFIX*$SUFFIX*" )"}%% *} ) }
_systemctl_unit_state() { typeset -gA _sys_unit_state; _sys_unit_state=( $(__systemctl list-unit-files "*$PREFIX*$SUFFIX*" ) ) }

local fun
# Completion functions for ALL_UNITS
for fun in is-active is-failed is-enabled status show cat mask preset help list-dependencies edit revert add-wants add-requires ; do
  (( $+functions[_systemctl_$fun] )) || _systemctl_$fun()
  {
    _systemctl_really_all_units
    _wanted systemd-units expl unit \
      compadd "$@" -a - _sys_really_all_units
  }
done

# Completion functions for ENABLED_UNITS
(( $+functions[_systemctl_disable] )) || _systemctl_disable()
{
    local _sys_unit_state; _systemctl_unit_state
    _wanted systemd-units expl 'enabled unit' \
      compadd "$@" - ${(k)_sys_unit_state[(R)enabled]}
}

(( $+functions[_systemctl_reenable] )) || _systemctl_reenable()
{
    local _sys_unit_state; _systemctl_unit_state
    _wanted systemd-units expl 'enabled/disabled unit' \
      compadd "$@" - ${(k)_sys_unit_state[(R)(enabled|disabled)]} $(_systemctl_get_template_names)
}

# Completion functions for DISABLED_UNITS
(( $+functions[_systemctl_enable] )) || _systemctl_enable()
{
  local _sys_unit_state; _systemctl_unit_state
  _wanted systemd-units expl 'disabled unit' \
    compadd "$@" - ${(k)_sys_unit_state[(R)disabled]} $(_systemctl_get_template_names)
}

# Completion functions for FAILED_UNITS
(( $+functions[_systemctl_reset-failed] )) || _systemctl_reset-failed()
{
  local _sys_failed_units; _systemctl_failed_units
  _wanted systemd-units expl 'failed unit' \
    compadd "$@" -a - _sys_failed_units || _message "no failed unit found"
}

# Completion functions for STARTABLE_UNITS
(( $+functions[_systemctl_start] )) || _systemctl_start()
{
   local _sys_startable_units; _systemctl_startable_units
   _wanted systemd-units expl 'startable unit' \
     compadd "$@" - ${_sys_startable_units[*]} $(_systemctl_get_template_names)
}

# Completion functions for STOPPABLE_UNITS
for fun in stop kill try-restart condrestart ; do
  (( $+functions[_systemctl_$fun] )) || _systemctl_$fun()
  {
    local _sys_active_units; _systemctl_active_units
    _wanted systemd-units expl 'stoppable unit' \
      compadd "$@" - $( _filter_units_by_property CanStop yes \
        ${_sys_active_units[*]} )
  }
done

# Completion functions for ISOLATABLE_UNITS
(( $+functions[_systemctl_isolate] )) || _systemctl_isolate()
{
  _systemctl_all_units
  _wanted systemd-units expl 'isolatable unit' \
    compadd "$@" - $( _filter_units_by_property AllowIsolate yes \
      ${_sys_all_units[*]} )
}

# Completion functions for RELOADABLE_UNITS
for fun in reload try-reload-or-restart force-reload ; do
  (( $+functions[_systemctl_$fun] )) || _systemctl_$fun()
  {
    local _sys_active_units; _systemctl_active_units
    _wanted systemd-units expl 'reloadable unit' \
      compadd "$@" - $( _filter_units_by_property CanReload yes \
        ${_sys_active_units[*]} )
  }
done

# Completion functions for RESTARTABLE_UNITS
for fun in restart reload-or-restart ; do
  (( $+functions[_systemctl_$fun] )) || _systemctl_$fun()
  {
    local _sys_restartable_units; _systemctl_restartable_units
    _wanted systemd-units expl 'restartable unit' \
      compadd "$@" - ${_sys_restartable_units[*]} $(_systemctl_get_template_names)
  }
done

# Completion functions for MASKED_UNITS
(( $+functions[_systemctl_unmask] )) || _systemctl_unmask()
{
  local _sys_unit_state; _systemctl_unit_state
  _wanted systemd-units expl 'masked unit' \
    compadd "$@" - ${(k)_sys_unit_state[(R)masked]} || _message "no masked units found"
}

# Completion functions for JOBS
(( $+functions[_systemctl_cancel] )) || _systemctl_cancel()
{
  _wanted systemd-jobs expl job \
    compadd "$@" - ${${(f)"$(__systemctl list-jobs)"}%% *} ||
      _message "no jobs found"
}

# Completion functions for TARGETS
(( $+functions[_systemctl_set-default] )) || _systemctl_set-default()
{
  _wanted systemd-targets expl target \
    compadd "$@" - ${${(f)"$(__systemctl list-unit-files --type target --all)"}%% *} ||
      _message "no targets found"
}

# Completion functions for ENVS
for fun in set-environment unset-environment ; do
  (( $+functions[_systemctl_$fun] )) || _systemctl_$fun()
  {
    local fun=$0 ; fun=${fun##_systemctl_}
    local suf
    if [[ "${fun}" = "set-environment" ]]; then
      suf='-S='
    fi
    _wanted systemd-environment expl 'environment variable' \
      compadd "$@" ${suf} - ${${(f)"$(systemctl show-environment)"}%%=*}
  }
done

(( $+functions[_systemctl_link] )) || _systemctl_link() {
   _sd_unit_files
}

(( $+functions[_systemctl_switch-root] )) || _systemctl_switch-root() {
   _files
}

# no systemctl completion for:
#    [STANDALONE]='daemon-reexec daemon-reload default
#                  emergency exit halt kexec list-jobs list-units
#                  list-unit-files poweroff reboot rescue show-environment'

_systemctl_caching_policy()
{
  local _sysunits
  local -a oldcache

  # rebuild if cache is more than a day old
  oldcache=( "$1"(mh+1) )
  (( $#oldcache )) && return 0

  _sysunits=(${${(f)"$(__systemctl --all)"}%% *})

  if (( $#_sysunits )); then
    for unit in $_sysunits; do
      [[ "$unit" -nt "$1" ]] && return 0
    done
  fi

  return 1
}

_unit_states() {
    local -a _states
    _states=("${(fo)$(__systemctl --state=help)}")
    _values -s , "${_states[@]}"
}

_unit_types() {
    local -a _types
    _types=("${(fo)$(__systemctl -t help)}")
    _values -s , "${_types[@]}"
}

_unit_properties() {
  if ( [[ ${+_sys_all_properties} -eq 0 ]] || _cache_invalid SYS_ALL_PROPERTIES$_sys_service_mgr ) ||
    ! _retrieve_cache SYS_ALL_PROPERTIES$_sys_service_mgr;
  then
    _sys_all_properties=( ${${(M)${(f)"$(__systemctl show --all;
    /usr/lib/systemd/systemd --dump-configuration-items)"}##[[:alnum:]]##=*}%%=*}
    )
    _store_cache SYS_ALL_PROPERTIES$_sys_service_mgr _sys_all_properties
  fi
  _values -s , "${_sys_all_properties[@]}"
}

_job_modes() {
    local -a _modes
    _modes=(fail replace replace-irreversibly isolate ignore-dependencies ignore-requirements flush)
    _values -s , "${_modes[@]}"
}

# Build arguments for "systemctl" to be used in completion.
local -a _modes; _modes=("--user" "--system")
# Use the last mode (they are exclusive and the last one is used).
local _sys_service_mgr=${${words:*_modes}[(R)(${(j.|.)_modes})]}
_arguments -s \
    {-h,--help}'[Show help]' \
    '--version[Show package version]' \
    {-t+,--type=}'[List only units of a particular type]:unit type:_unit_types' \
    '--state=[Display units in the specified state]:unit state:_unit_states' \
    '--job-mode=[Specify how to deal with other jobs]:mode:_job_modes' \
    {-p+,--property=}'[Show only properties by specific name]:unit property:_unit_properties' \
    {-a,--all}'[Show all units/properties, including dead/empty ones]' \
    '--reverse[Show reverse dependencies]' \
    '--after[Show units ordered after]' \
    '--before[Show units ordered before]' \
    {-l,--full}"[Don't ellipsize unit names on output]" \
    '--show-types[When showing sockets, show socket type]' \
    {-i,--ignore-inhibitors}'[When executing a job, ignore jobs dependencies]' \
    {-q,--quiet}'[Suppress output]' \
    '--no-block[Do not wait until operation finished]' \
    '--no-legend[Do not print a legend, i.e. the column headers and the footer with hints]' \
    '--no-pager[Do not pipe output into a pager]' \
    '--system[Connect to system manager]' \
    '--user[Connect to user service manager]' \
    "--no-wall[Don't send wall message before halt/power-off/reboot]" \
    '--global[Enable/disable unit files globally]' \
    "--no-reload[When enabling/disabling unit files, don't reload daemon configuration]" \
    '--no-ask-password[Do not ask for system passwords]' \
    '--kill-who=[Who to send signal to]:killwho:(main control all)' \
    {-s+,--signal=}'[Which signal to send]:signal:_signals' \
    {-f,--force}'[When enabling unit files, override existing symlinks. When shutting down, execute action immediately]' \
    '--root=[Enable unit files in the specified root directory]:directory:_directories' \
    '--runtime[Enable unit files only temporarily until next reboot]' \
    {-H+,--host=}'[Operate on remote host]:userathost:_sd_hosts_or_user_at_host' \
    {-P,--privileged}'[Acquire privileges before execution]' \
    {-n+,--lines=}'[Journal entries to show]:number of entries' \
    {-o+,--output=}'[Change journal output mode]:modes:_sd_outputmodes' \
    '--firmware-setup[Tell the firmware to show the setup menu on next boot]' \
    '--plain[When used with list-dependencies, print output as a list]' \
    '--failed[Show failed units]' \
    '*::systemctl command:_systemctl_command'
}

vcs_info() {
## vim:ft=zsh:foldmethod=marker
##
## vcs_info - provide version control information
##
## Written by Frank Terbeck <ft@bewatermyfriend.org>
##
## This file and all corresponding files in Functions/VCS_Info/ are
## distributed under the same BSD-ish license as zsh itself.
##

setopt localoptions noksharrays extendedglob NO_shwordsplit
local file func sys
local -a static_functions msgs
local -i maxexports

static_functions=(
    VCS_INFO_adjust
    VCS_INFO_bydir_detect
    VCS_INFO_check_com
    VCS_INFO_formats
    VCS_INFO_get_cmd
    VCS_INFO_hexdump
    VCS_INFO_hook
    VCS_INFO_set-patch-format
    VCS_INFO_maxexports
    VCS_INFO_nvcsformats
    VCS_INFO_patch2subject
    VCS_INFO_quilt
    VCS_INFO_realpath
    VCS_INFO_reposub
    VCS_INFO_set

    vcs_info_hookadd
    vcs_info_hookdel
    vcs_info_lastmsg
    vcs_info_printsys
    vcs_info_setsys
)

for func in ${static_functions} ; do
    autoload -Uz ${func}
done

[[ -n ${(Mk)parameters:#vcs_info_msg_<->_} ]] && unset ${parameters[(I)vcs_info_msg_<->_]}
VCS_INFO_maxexports
VCS_INFO_set --nvcs '-preinit-'
vcs_info_setsys

# and now, finally create the real vcs_info function
vcs_info () {
    emulate -L zsh
    setopt extendedglob NO_warn_create_global

    [[ -r . ]] || return 0

    local pat
    local -i found retval
    local -a enabled disabled dps
    local usercontext vcs rrn quiltmode
    local -x LC_MESSAGES
    local -i maxexports
    local -a msgs
    local -A vcs_comm hook_com backend_misc user_data

    LC_MESSAGES=C
    if [[ -n ${LC_ALL} ]]; then
        local -x LANG
        LANG=${LC_ALL}
        local -x LC_ALL
    fi
    vcs='-init-'; rrn='-all-'; quiltmode='addon'
    usercontext=${1:-default}

    VCS_INFO_hook "start-up"
    retval=$?
    if (( retval == 1 )); then
        return 0
    elif (( retval == 2 )); then
        # This needs `max-exports' set. We're still setting it again later
        # for more specific contexts.
        VCS_INFO_maxexports
        VCS_INFO_set --nvcs
        return 0
    fi

    zstyle -a ":vcs_info:${vcs}:${usercontext}:${rrn}" "enable" enabled
    (( ${#enabled} == 0 )) && enabled=( all )

    if [[ -n ${(M)enabled:#(#i)none} ]] ; then
        [[ -n ${vcs_info_msg_0_} ]] && VCS_INFO_set --nvcs
        return 0
    fi

    if [[ -n ${(M)enabled:#(#i)all} ]] ; then
        enabled=( ${VCS_INFO_backends} )
        zstyle -a ":vcs_info:${vcs}:${usercontext}:${rrn}" "disable" disabled
    fi

    zstyle -a ":vcs_info:${vcs}:${usercontext}:${rrn}" "disable-patterns" dps

    for pat in ${dps} ; do
        if [[ ${PWD} == ${~pat} ]] ; then
            VCS_INFO_maxexports
            [[ -n ${vcs_info_msg_0_} ]] && VCS_INFO_set --nvcs
            return 0
        fi
    done

    VCS_INFO_maxexports

    (( found = 0 ))
    for vcs in ${enabled} ; do
        [[ -n ${(M)disabled:#${vcs}} ]] && continue
        if (( ${+functions[VCS_INFO_detect_${vcs}]} == 0 )) ; then
            printf 'vcs_info: configured unknown backend: '\''%s'\''\n' ${vcs}
            printf 'vcs_info: use '\''vcs_info_printsys'\'' to find supported systems.\n'
            continue
        fi
        vcs_comm=()
        VCS_INFO_get_cmd
        VCS_INFO_detect_${vcs} && (( found = 1 )) && break
    done

    (( found == 0 )) && {
        vcs='-quilt-'; quiltmode='standalone'
        VCS_INFO_quilt standalone || VCS_INFO_set --nvcs
        return 0
    }

    VCS_INFO_hook "pre-get-data"
    retval=$?
    if (( retval == 1 )); then
        return 0
    elif (( retval == 2 )); then
        VCS_INFO_set --nvcs
        return 0
    fi

    VCS_INFO_get_data_${vcs} || {
        VCS_INFO_set --nvcs
        return 1
    }

    VCS_INFO_set
    return 0
}

vcs_info "$@"
}
