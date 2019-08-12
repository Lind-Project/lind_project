set number
set relativenumber
set tabstop=4
set shiftwidth=4
set expandtab
set number
set cin
set nocp
set nocompatible              " be iMproved, required
syntax on

let mapleader = ","

nnoremap <up> <nop>
nnoremap <right> <nop>
nnoremap <left> <nop>
nnoremap <down> <nop>
vnoremap <up> <nop>
vnoremap <right> <nop>
vnoremap <left> <nop>
vnoremap <down> <nop>
inoremap <up> <nop>
inoremap <right> <nop>
inoremap <left> <nop>
inoremap <down> <nop>

nnoremap <c-j> <c-w>j
nnoremap <c-k> <c-w>k
nnoremap <c-h> <c-w>h
nnoremap <c-l> <c-w>l

set hls
nnoremap <silent> <leader>, :noh<CR>
nnoremap <leader>a ^whv],hdli v$hp^wP

nnoremap <leader>b !!bash<CR>
nnoremap <leader>c !!bc -l<CR>
nnoremap <leader>u :source ~/.vimrc<CR>

autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
noremap <C-T> :<C-U>NERDTreeToggle<CR>

filetype off                  " required
set rtp+=~/.vim/bundle/Vundle.vim

call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'itchyny/lightline.vim'
Plugin 'mattn/emmet-vim'
Plugin 'pangloss/vim-javascript'
Plugin 'mxw/vim-jsx'
Plugin 'tpope/vim-vinegar'
Plugin 'tpope/vim-surround'
Plugin 'tpope/vim-commentary'
Plugin 'tpope/vim-fugitive'
Plugin 'tpope/vim-apathy'
Plugin 'christoomey/vim-sort-motion'
Plugin 'tmhedberg/matchit'
Plugin 'scrooloose/nerdtree'
Plugin 'aserebryakov/vim-todo-lists'
Plugin 'kmyk/sdl2.vim'
Plugin 'bfrg/vim-cpp-modern'
Plugin 'tpope/vim-rhubarb'
Plugin 'calculuswhiz/vim-GAS-x86_64-highlighter'
Plugin 'tpope/vim-eunuch'
Plugin 'dhruvasagar/vim-table-mode'
Plugin 'PeterRincker/vim-argumentative'
Plugin 'Siphalor/vim-atomified'
Plugin 'christoomey/vim-tmux-navigator'
call vundle#end()            " required

filetype plugin indent on    " required

set laststatus=2
let g:lightline = {
      \ 'colorscheme': 'wombat',
      \ }
let g:user_emmet_install_global = 0
autocmd FileType html,css,js EmmetInstall

autocmd BufWritePre * :normal g_ld$ 

if !has("gui_running")
	let &t_AB="\e[48;5;%dm"
	let &t_AF="\e[38;5;%dm"
    colorscheme atomified
endif
hi Normal ctermbg=234 ctermfg=White guifg=Black guibg=White
set encoding=utf-8
packadd termdebug
"OH MY GOD GDB INTEGRATION IS SO GOOD
nnoremap gdb :Termdebug<CR>
augroup remember_folds
  autocmd!
  autocmd BufWinLeave * mkview
  autocmd BufWinEnter * silent! loadview
augroup END
cnoremap w!! execute 'silent! write !sudo tee % >/dev/null' <bar> edit!
autocmd BufNewFile,BufRead *.repy set syntax=python
