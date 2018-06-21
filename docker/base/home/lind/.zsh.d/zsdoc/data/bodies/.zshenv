

export ZSH="/usr/share/zsh"
[[ ! -f "${HOME}/.profile" ]] || \
	emulate sh -c '. "${HOME}/.profile"'
[[ ! -f "/etc/profile.d/cnf.sh" ]] || \
	emulate sh -c '. "/etc/profile.d/cnf.sh"'
[[ ! -f "${HOME}/perl5/perlbrew/etc/bashrc" ]] || \
	emulate bash -c '. "${HOME}/perl5/perlbrew/etc/bashrc"'
[[ ! -f "${ZDOTDIR:-$HOME}/.zwidgets" ]] || \
	. "${ZDOTDIR:-$HOME}/.zwidgets"
