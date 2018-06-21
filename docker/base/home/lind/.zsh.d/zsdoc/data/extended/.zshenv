#!/usr/bin/env zsh
#
# .zshenv
#
# zsh environment

export ZSH="/usr/share/zsh"

# enable gnome keyring for applications run through the terminal, such as SSH
# if [[ -n "$DESKTOP_SESSION" ]]; then
#         #pgrep -x gnome-keyring-daemon >/dev/null 2>&1 && eval "$(gnome-keyring-daemon -r -c secrets 2>/dev/null)"
#         eval "$(gnome-keyring-daemon -s -c secrets 2>/dev/null)"
#         export SSH_AUTH_SOCK
# fi

# source personal dotfiles
[[ ! -f "${HOME}/.profile" ]] || \
	emulate sh -c '. "${HOME}/.profile"'
# source command-not-found files.
[[ ! -f "/etc/profile.d/cnf.sh" ]] || \
	emulate sh -c '. "/etc/profile.d/cnf.sh"'
# source perlbrew completions
[[ ! -f "${HOME}/perl5/perlbrew/etc/bashrc" ]] || \
	emulate bash -c '. "${HOME}/perl5/perlbrew/etc/bashrc"'
# define ZLE widgets
[[ ! -f "${ZDOTDIR:-$HOME}/.zwidgets" ]] || \
	. "${ZDOTDIR:-$HOME}/.zwidgets"
