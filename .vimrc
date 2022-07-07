set nocompatible              " be iMproved, required
filetype off                  " required

set number
set autoindent
"Fold commands"
nnoremap <space> za
set foldmethod=syntax
set foldlevel=20
au BufWinLeave * mkview
au BufWinEnter * silent loadview


" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
Plugin 'tpope/vim-fugitive'
" plugin from http://vim-scripts.org/vim/scripts.html
" Plugin 'L9'
" Git plugin not hosted on GitHub
Plugin 'git://git.wincent.com/command-t.git'
" git repos on your local machine (i.e. when working on your own plugin)
Plugin 'file:///home/gmarik/path/to/plugin'
" The sparkup vim script is in a subdirectory of this repo called vim.
" Pass the path to set the runtimepath properly.
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}
" Install L9 and avoid a Naming conflict if you've already installed a
" different version somewhere else.
" Plugin 'ascenator/L9', {'name': 'newL9'}

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
Plugin 'morhetz/gruvbox'
colorscheme gruvbox
syntax on
set background=dark

Plugin 'scrooloose/nerdtree'

autocmd vimenter * NERDTree

Plugin 'tc50cal/vim-terminal'

inoremap { {}<Esc>:let leavechar="}"<CR>i
inoremap ( ()<Esc>:let leavechar=")"<CR>i
inoremap [ []<Esc>:let leavechar="]"<CR>i
inoremap " ""<Esc>:let leavechar="""<CR>i
inoremap ' ''<Esc>:let leavechar="'"<CR>i

""autocmd filetype cpp nnoremap <F4> :w <bar> exec '!g++ '.shellescape('%').' -o '.shellescape('%:r').' && ./'.shellescape('%:r')<CR>
autocmd FileType python nnoremap r :w<CR>:exec '!python3' shellescape(@%, 1)<CR>
%
"g++ -std=c++14 -Wshadow -Wall -o -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
autocmd filetype cpp nnoremap r :w <bar> exec '!g++ -std=c++14 '.shellescape('%').'  -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -o '.shellescape('%:r').' && ./'.shellescape('%:r')<CR>

"autocmd filetype cpp nnoremap r :w <bar> exec '!g++ -std=c++14 '.shellescape('%').' -o '.shellescape('%:r').' && ./'.shellescape('%:r')<CR>
%
autocmd filetype cpp nnoremap t :w <bar> exec '!g++ -std=c++14 *.cpp -o main && ./main'<CR>
%
