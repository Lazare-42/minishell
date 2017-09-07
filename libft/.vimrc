set nocompatible

filetype indent on
syntax enable
set encoding=utf-8
set t_Co=256
set cc=80
set ai
set number
set mouse=a
set cursorline
set showcmd
set showmatch
set ruler
set ignorecase
set hlsearch
colorscheme gruvbox
set background=dark

set tabstop=4
set shiftwidth=4


"Syntastic ////////////////////////////////////////////////////////////////////
execute pathogen#infect()
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*
let current_compiler = "gcc"
let g:syntastic_check_on_open=1
let g:syntastic_enable_signs=1
let g:syntastic_c_remove_include_errors = 1
let g:syntastic_c_include_dirs = ['../../../include', '../../include','../include','./include']
let g:syntastic_c_compiler_options ='-Wall -Werror -Wextra'
"//////////////////////////////////////////////////////////////////////////////
