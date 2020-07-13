#!/bin/sh
#
# .profile - environment configuration

# conditionals
if command -v bat >/dev/null 2>&1; then
	if command -v b >/dev/null 2>&1; then
		dump_cmd="b"
	else
		dump_cmd="bat"
	fi
elif command -v less >/dev/null 2>&1; then
	dump_cmd="less"
else
	dump_cmd="cat"
fi
if command -v ruby >/dev/null 2>&1; then
	rubies="$(ruby -rrubygems -e "puts Gem.user_dir")/bin"
else
	rubies=""
fi
if [ "$TERM" != linux ] && [ "$TERM" != xterm ] && [ -d "$HOME/.terminfo" ]; then
	TERM=screen-256color-italic
fi
if [ "$(hostname)" != localhost ] && [ "$(hostname)" != fedora ] && [ "$(hostname)" != fedoravm ]; then
	locale="en_US.UTF-8"
fi
if command -v nproc >/dev/null 2>&1; then
	NPROC="$(nproc)"
else
	NPROC=2
fi
if [ -t 0 ]; then
	stty -ixon
fi
export NPROC

# directory shortcut environment variables
export CONFIG="/store/dotfiles"
export LINUX="$PROJECTS/linux"
export PROJECTS="/store/code/projects"
export C="$CONFIG" H="$HOME" L="$LINUX" P="$PROJECTS"

# compiler environment
unset CARCH CCACHE_DISABLE CFLAGS CCFLAGS
unset CHOST C_INCLUDE_PATH CPATH CPPFLAGS
unset CXXFLAGS LDFLAGS LIBRARY_PATH
# export CARCH="x86_64"
export CCACHE_DIR="$HOME/.ccache"
export CCACHE_DISABLE=1
# export CCACHE_PATH=/usr/bin
# export CCACHE_PREFIX="distcc"
export CCACHE_TEMPDIR="$CCACHE_DIR/tmp"
# sparse configuraiton
CF="-DCONFIG_SPARSE_RCU_POINTER -D__CHECK_ENDIAN__"
# CF="$CF -fmax-warnings=unlimited"
CF="$CF -Wptr-subtraction-blows -Wtypesign"
CF="$CF -Wdefault-bitfield-sign -Wparen-string"
CF="$CF -Wno-undef -Wno-unknown-attribute"
CF="$CF -Wno-pointer-arith -Wno-shadow -Wno-sizeof-bool"
CF="$CF -Wno-do-while -Wno-non-pointer-null"
export CF
export DISTCC_HOSTS="127.0.0.1,lzo,cpp 192.168.1.99,lzo,cpp"
GCC_COLORS="error=01;31:warning=01;35:note=01;36:range1=32:range2=34"
GCC_COLORS="$GCC_COLORS:caret=01;32:locus=01:quote=01:fixit-insert=32:fixit-delete=31"
GCC_COLORS="$GCC_COLORS:diff-filename=01:diff-hunk=32:diff-delete=31:diff-insert=32"
GCC_COLORS="$GCC_COLORS:type-diff=01;32"
export GCC_COLORS
# compiler flags
CFLAGS="-Wno-error -Wno-implicit-fallthrough"
# CFLAGS="$CFLAGS -flto"
# CFLAGS="$CFLAGS -fno-common"
# CFLAGS="$CFLAGS -fvar-tracking -fvar-tracking-assignments"
# CFLAGS="$CFLAGS -fdiagnostics-color=always"
# CFLAGS="$CFLAGS -fdiagnostics-generate-patch"
CFLAGS="$CFLAGS -fno-strict-aliasing -fno-plt -fPIC"
CFLAGS="$CFLAGS -fuse-ld=gold -fuse-linker-plugin"
# CFLAGS="$CFLAGS -march=native -gdwarf-4 -g3 -O3"
# CFLAGS="$CFLAGS -march=x86-64 -mtune=intel -g3 -O3"
# CFLAGS="$CFLAGS -pipe -march=native -g -O3"
# CFLAGS="$CFLAGS -pipe -march=x86-64 -mtune=generic -g -O3"
CFLAGS="$CFLAGS -pipe -march=x86-64 -mtune=generic -O2"
export CFLAGS
# export CHOST="x86_64-unknown-linux-gnu"
# export CPATH=":$HOME/.local/include"
# export C_INCLUDE_PATH=":$HOME/.local/include"
# export CPPFLAGS="-D_FORTIFY_SOURCE=2"
export CXXFLAGS="$CFLAGS"
LDFLAGS="$CFLAGS"
# LDFLAGS="$LDFLAGS -Wl,--warn-unresolved-symbols"
LDFLAGS="$LDFLAGS -Wl,-O2,-z,relro,-z,now,-z,noexecstack"
LDFLAGS="$LDFLAGS -Wl,--as-needed,--sort-common,--warn-common"
export LDFLAGS
# export LIBRARY_PATH="$HOME/.local/lib"
# export MAKEFLAGS="-j -l$NPROC"
export MAKEFLAGS="-j$((NPROC + 2)) -l$NPROC"

# Environment variables
export ARCHFLAGS="-arch x86-64"
# export BROWSER=firefox
# export BROWSER=chromium
# export BROWSER=w3m
# export BROWSER=lynx
# export BROWSER=netsurf
export CLICOLOR=1
export CORRECT_IGNORE='_?*'
# Audio plugins
DSSI_PATH="/usr/local/lib/dssi:/usr/lib/dssi"
DSSI_PATH="$HOME/dssi:/store/audio/dssi:$DSSI_PATH"
export DSSI_PATH
# Add vim as default editor
export EDITOR=vim
export FCEDIT="$EDITOR" SUDO_EDITOR="$EDITOR" SYSTEMD_EDITOR="$EDITOR" VISUAL="$EDITOR"
export FREETYPE_PROPERTIES="truetype:interpreter-version=35"
# FZF_DEFAULT_COMMAND="(git ls-tree -r --name-only HEAD"
# FZF_DEFAULT_COMMAND="$FZF_DEFAULT_COMMAND || find . -path '*/\\.*' -prune -o"
# FZF_DEFAULT_COMMAND="$FZF_DEFAULT_COMMAND \\( -type f -o -type l \\) -print"
# FZF_DEFAULT_COMMAND="$FZF_DEFAULT_COMMAND | sed s/^..//) 2>/dev/null"
# shellcheck disable=SC2089
FZF_DEFAULT_COMMAND="ag -g ''"
FZF_DEFAULT_OPTS="--color fg:-1,bg:-1,hl:230,fg+:3,bg+:233,hl+:229"
FZF_DEFAULT_OPTS="$FZF_DEFAULT_OPTS --color info:150,prompt:110,spinner:150,pointer:167,marker:174"
FZF_DEFAULT_OPTS="$FZF_DEFAULT_OPTS --height 40%"
FZF_DEFAULT_OPTS="$FZF_DEFAULT_OPTS --reverse"
# shellcheck disable=SC2089
FZF_ALT_C_OPTS="$FZF_DEFAULT_OPTS --preview 'tree -C {} | head -200'"
# shellcheck disable=SC2089
FZF_CTRL_R_OPTS="$FZF_DEFAULT_OPTS --preview 'echo {}'"
FZF_CTRL_R_OPTS="$FZF_CTRL_R_OPTS --preview-window down:3:hidden"
FZF_CTRL_R_OPTS="$FZF_CTRL_R_OPTS --bind '?:toggle-preview'"
FZF_CTRL_T_COMMAND="$FZF_DEFAULT_COMMAND"
# Using highlight (http://www.andre-simon.de/doku/highlight/en/highlight.html)
# shellcheck disable=SC2089
FZF_CTRL_T_OPTS="$FZF_DEFAULT_OPTS --preview '(highlight -O ansi -l {}"
FZF_CTRL_T_OPTS="$FZF_CTRL_T_OPTS || cat {} || tree -C {}) 2>/dev/null | head -200'"
# shellcheck disable=SC2090
export FZF_ALT_C_OPTS FZF_CTRL_R_OPTS FZF_CTRL_T_OPTS
# shellcheck disable=SC2090
export FZF_DEFAULT_OPTS FZF_CTRL_T_COMMAND FZF_DEFAULT_COMMAND
# export GDK_DPI_SCALE=0.4
# export GDK_SCALE=2.25
export GIT_PAGER="less -MRins"
export GOPATH="$HOME/.go"
export GROFF_NO_SGR=1
# Gtk themes
# export GTK_DEBUG=all
export GTK_IM_MODULE="xim" QT_IM_MODULE="xim" XMODIFIERS="@im=none"
# export GTK_IM_MODULE="fcitx" QT_IM_MODULE="fcitx" XMODIFIERS="@im=fcitx"
# export GTK_IM_MODULE="ibus" QT_IM_MODULE="ibus" XMODIFIERS="@im=ibus"
export GTK2_RC_FILES="$HOME/.gtkrc-2.0"
# get more colors
export HH_CONFIG=hicolor
INFOPATH="/usr/local/texlive/2016/texmf-dist/doc/info:/usr/share/info"
INFOPATH="$HOME/GNUstep/Library/Documentation/info:$INFOPATH"
INFOPATH="$HOME/.linuxbrew/share/info:$INFOPATH"
INFOPATH="$HOME/.local/share/.info:$INFOPATH"
export INFOPATH
export _JAVA_AWT_WM_NONREPARENTING=1
_JAVA_OPTIONS="-Dswing.aatext=true -Dawt.useSystemAAFontSettings=on"
_JAVA_OPTIONS="$_JAVA_OPTIONS -Dsun.java2d.opengl=true"
export _JAVA_OPTIONS
# Configure KWin to use OpenGL ES
export KWIN_COMPOSE="O2ES"
export LADSPA_PATH="/usr/lib/ladspa:/usr/local/lib/ladspa:$HOME/ladspa:/store/audio/ladspa"
export LANG="$locale"
export LANGUAGE="$locale"
unset LC_ALL
# export LC_ALL="$locale"
export LC_COLLATE="C"
# export LC_COLLATE="$locale"
export LC_CTYPE="$locale"
export LC_NUMERIC="$locale"
export LC_TIME="$locale"
export LC_MONETARY="$locale"
export LC_MESSAGES="$locale"
export LC_PAPER="$locale"
export LC_NAME="$locale"
export LC_ADDRESS="$locale"
export LC_TELEPHONE="$locale"
export LC_MEASUREMENT="$locale"
export LC_IDENTIFICATION="$locale"
export LOCALE="C"
export LV2_PATH="/usr/lib/lv2:/usr/local/lib/lv2:$HOME/lv2:/store/audio/lv2"
export LXVST_PATH="/usr/lib/lxvst:/usr/local/lib/lxvst:$HOME/lxvst:/store/audio/lxvst"
# export LESS=MNRXis
export LESS="FMRXins"
# shellcheck disable=SC2039
export LESS_TERMCAP_se=$'\E[0m' LESS_TERMCAP_me=$'\E[0m' LESS_TERMCAP_us=$'\E[4;32;4;132m'
# shellcheck disable=SC2039
export LESS_TERMCAP_ue=$'\E[0m' LESS_TERMCAP_so=$'\E[30;43m' LESS_TERMCAP_md=$'\E[1;31m'
export MANPAGER="env -u LESS less -MRins"
MANPATH="/usr/lib/plan9/man:/usr/local/texlive/2016/texmf-dist/doc/man"
MANPATH="/opt/intel/man/common:/usr/local/man:/usr/share/man:$MANPATH"
MANPATH="$HOME/.local/share/man:$MANPATH"
export MANPATH
export MANSECT="1:2:3:9:0:7:5:4:n:l:8:6:3f"
export MESA_GL_VERSION_OVERRIDE="4.5COMPAT"
export npm_config_prefix="$HOME/.node_modules"
# export PAGER=vimpager
export PAGER=less
# default PATH
PATH="/bin:/sbin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:$PATH"
PATH="/usr/bin/core_perl:/usr/bin/site_perl:/usr/bin/vendor_perl:$PATH"
PATH="/usr/lib/surfraw:/usr/lib/jvm/default/bin:$PATH"
PATH="/usr/lib/ccache/bin:$PATH"
PATH="/opt/android-sdk/platform-tool:$PATH"
PATH="/opt/TIS-100:/opt/cuda/bin:$PATH"
PATH="/opt/cross/bin:/opt/intel/bin:$PATH"
PATH="$HOME/.node_modules/bin:$PATH"
PATH="$HOME/.cargo/bin:$PATH"
PATH="$HOME/perl5/bin:$PATH"
PATH="$rubies:$PATH"
PATH="$LINUX/scripts:$PATH"
PATH="$HOME/.local/bin:$HOME/bin:$PATH"
# shellcheck disable=SC2039
# elide empty PATH components
PATH="${PATH//::/:}"
export PATH
# shellcheck disable=SC2039
PERL5LIB="$HOME/perl5/lib/perl5${PERL5LIB:+:${PERL5LIB//:$HOME\/perl5\/lib\/perl5}}"
# shellcheck disable=SC2039
PERL5LIB="${PERL5LIB:+${PERL5LIB//:$HOME\/perl5\/lib\/perl5}}"
export PERL5LIB
# shellcheck disable=SC2039
PERL_LOCAL_LIB_ROOT="$HOME/perl5${PERL_LOCAL_LIB_ROOT:+:${PERL_LOCAL_LIB_ROOT//:$HOME\/perl5}}"
# shellcheck disable=SC2039
PERL_LOCAL_LIB_ROOT="${PERL_LOCAL_LIB_ROOT:+${PERL_LOCAL_LIB_ROOT//:$HOME\/perl5}}"
export PERL_LOCAL_LIB_ROOT
export PERL_MB_OPT="--install_base \"$HOME/perl5\""
export PERL_MM_OPT="INSTALL_BASE=\"$HOME/perl5\""
export PERLDOC="-i -oman"
# export PERLDOC_PAGER="most -+C -E"
# export PERLDOC_PAGER="less -+C -MRXs"
export PERLDOC_PAGER="less -MRins"
# export PLAN9=/usr/lib/plan9 PATH="$PATH:$PLAN9/bin"
PKG_CONFIG_PATH="/usr/local/lib/pkgconfig:/usr/lib/pkgconfig"
PKG_CONFIG_PATH="$HOME/.local/lib/pkgconfig:$PKG_CONFIG_PATH"
export PKG_CONFIG_PATH
# export PLAN9=/usr/lib/plan9 PATH="${PATH//:\/usr\/lib\/plan9\/bin}:$PLAN9/bin"
export PLAN9=/opt/plan9
# shellcheck disable=SC2039
export PATH="${PATH//:$PLAN9\/bin}$PLAN9/bin" MANPATH="${MANPATH//:$PLAN9\/man}:$PLAN9/share/man"
export PRE="$HOME/.local" pre="$PRE"
export PS_FORMAT="flags,uid,pid,ppid,tpgid,pgrp,session,pri,ni,pcpu,sz,wchan,stat,state,tname,time,args"
# Python2 compatibility
# export PYTHON="/usr/bin/python2"
export PYTHONSTARTUP="$HOME/.pythonrc"
export READNULLCMD="$dump_cmd"
export REPORTTIME=5
export RLWRAP_EDITOR="vim '+call cursor(%L,%C)'"
export QEMU_AUDIO_DRV=pa
export QEMU_PA_SERVER=localhost
export QT_AUTO_SCREEN_SCALE_FACTOR=1
export QT_PLUGIN_PATH="$HOME/.kde4/lib/kde4/plugins:/usr/lib/kde4/plugins"
export QT_QPA_PLATFORMTHEME=qt5ct
# export QT_SCALE_FACTOR=2.25
# increase history size (default is 500)
export HISTSIZE=1000000
export HISTFILESIZE="$HISTSIZE" SAVEHIST="$HISTSIZE"
# export QT_SCREEN_SCALE_FACTORS=2.25
export SDL_AUDIODRIVER=alsa
export SSH_KEY_PATH="$HOME/.ssh/id_gpg"
SURF_USERAGENT="Mozilla/5.0 (Linux; Android 6.0.1; Nexus 5 Build/MOB3OD)"
SURF_USERAGENT="$SURF_USERAGENT AppleWebKit/537.36 (KHTML, like Gecko)"
SURF_USERAGENT="$SURF_USERAGENT Chrome/49.0.2623.105 Mobile Safari/537.36"
export SURF_USERAGENT
export SYSTEMD_LESS="FKMRins"
export TERMINAL=st
TIME="%J
[system: %S] [elapsed: %E] [cpu: %P]
[swaps: %W] ([major: %F]+[minor: %R] pagefaults)
[input: %I]+[output: %O] ([text: %Xk]+[data: %Dk] [max: %Mk] memory)
[exit: %W] ([voluntary: %w]+[involuntary: %c] context-switches)"
TIMEFMT="$TIME"
export TiME TIMEFMT
export TZ=/usr/share/zoneinfo/posix/Pacific/Honolulu
export VST_PATH="$HOME/vst:/store/audio/vst:/usr/lib/vst:/usr/local/lib/vst"
# export VIRTUALENVWRAPPER_PYTHON=/usr/bin/python3
export VIRTUALENVWRAPPER_PYTHON=/usr/bin/python2
# export VIRTUALENVWRAPPER_VIRTUALENV=/usr/bin/virtualenv
export VIRTUALENVWRAPPER_VIRTUALENV=/usr/bin/virtualenv2
# define word separators (for stuff like backward-word, forward-word, backward-kill-word,..)
export WORDCHARS=''
# export WORDCHARS='_-*~'
# export WORDCHARS='*?_-.[]~=/&;!#$%^ (){}<>'
export WORKON_HOME="$HOME/.virtualenvs"
# Set X cursor theme
export XCURSOR_THEME="Oxygen_Blue"
# export XCURSOR_THEME=ArchCursorTheme
export XDG_CACHE_HOME="$HOME/.cache"
export XDG_CONFIG_DIRS="$HOME/.config:/etc/xdg"
# export XDG_CONFIG_HOME="$HOME/.config"
export XDG_CONFIG_HOME="$HOME/.local/etc"
export XDG_DATA_DIRS="/usr/local/share:/usr/share"
export XDG_DATA_HOME="$HOME/.local/share"
export ZDOTDIR="$HOME/.zsh.d"

# zsh z plugin environment
#
# maintains a jump-list of the directories you actually use
#
# INSTALL:
#     * put something like this in your .bashrc/.zshrc:
#         . /path/to/z.sh
#     * cd around for a while to build up the db
#     * PROFIT!!
#     * optionally:
#         set $_Z_CMD in .bashrc/.zshrc to change the command (default z).
#         set $_Z_DATA in .bashrc/.zshrc to change the datafile (default ~/.z).
#         set $_Z_NO_RESOLVE_SYMLINKS to prevent symlink resolution.
#         set $_Z_NO_PROMPT_COMMAND if you're handling PROMPT_COMMAND yourself.
#         set $_Z_EXCLUDE_DIRS to an array of directories to exclude.
#         set $_Z_OWNER to your username if you want use z while sudo with $HOME kept
#
# USE:
#     * z foo     # cd to most frecent dir matching foo
#     * z foo bar # cd to most frecent dir matching foo and bar
#     * z -r foo  # cd to highest ranked dir matching foo
#     * z -t foo  # cd to most recently accessed dir matching foo
#     * z -l foo  # list matches instead of cd
#     * z -c foo  # restrict matches to subdirs of $PWD
unset _Z_CMD _Z_DATA _Z_NO_RESOLVE_SYMLINKS
unset _Z_NO_PROMPT_COMMAND _Z_EXCLUDE_DIRS
unset _Z_OWNER _FASD_SINK _last_z_args
export _Z_NO_RESOLVE_SYMLINKS=true
# export _Z_NO_PROMPT_COMMAND=true
# export _Z_OWNER=alyptik
# export _FASD_SINK="/store/.fasd.log"
# used to track arguments of last `z` command
export _last_z_args

# vi:ft=sh:
