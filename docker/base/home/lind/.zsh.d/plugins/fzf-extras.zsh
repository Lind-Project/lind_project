# ALT-I - Paste the selected entry from locate output into the command line
fzf-locate-widget() {
	local selected
	# if selected=$(locate / | fzf -q "$LBUFFER"); then
	selected=$(locate / | \
		FZF_DEFAULT_OPTS="--height ${FZF_TMUX_HEIGHT:-40%} --reverse $FZF_DEFAULT_OPTS $FZF_ALT_C_OPTS" \
		$(__fzfcmd) -q "$LBUFFER")
	LBUFFER=$selected
	zle redisplay
}

zle     -N    fzf-locate-widget
bindkey '\ei' fzf-locate-widget
