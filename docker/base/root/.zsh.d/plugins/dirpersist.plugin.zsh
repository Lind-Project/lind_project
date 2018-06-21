#!/bin/zsh
# Make the dirstack more persistant
#
# Add dirpersist to $plugins in ~/.zshrc to load
#
# $zdirstore is the file used to persist the stack

export zdirstore="${ZDOTDIR:-$HOME}/.zdirstore"

dirpersistinstall () {
    if grep 'dirpersiststore' "${ZDOTDIR:-$HOME}/.zlogout" >/dev/null; then
    else
        if read -q \?"Would you like to set up your .zlogout file for use with dirspersist? (y/n) "; then
            echo "# Store dirs stack\n\n" >> "${ZDOTDIR:-$HOME}/.zlogout"
        else
            echo "If you don't want this message to appear, remove dirspersist from \$plugins"
        fi
    fi
}

dirpersiststore () {
    dirs -p | perl -e 'foreach (reverse <STDIN>) {chomp;s/([& ])/\\$1/g ;print "if [ -d $_ ]; then pushd -q $_; fi\n"}' > "$zdirstore"
}

dirpersistrestore () {
    if [[ -f "$zdirstore" ]]; then
        source "$zdirstore"
    fi
}

DIRSTACKSIZE=10
setopt autopushd pushdminus pushdsilent pushdtohome pushdignoredups
#setopt autopushd pushdsilent pushdtohome pushdignoredups

dirpersistinstall
dirpersistrestore

# Make popd changes permanent without having to wait for logout
alias popd="popd; dirpersiststore"
chpwd_functions+=(dirpersiststore)
