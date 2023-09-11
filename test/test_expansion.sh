#!/bin/bash

assert() {
    printf '%-30s:' "\"$1\""

		if [ ! -e "out" ]; then
						touch out
		fi
    echo -n -e "$1" | bash >cmp | exec >&-
    echo -n -e "$1" | bash
    expected=$?

    echo -n -e "$1" | ./minishell >out | exec >&-
    echo -n -e "$1" | ./minishell
    actual=$?

    diff cmp out >/dev/null && echo -n -e '  diff \033[0;32mOK\033[0;37m' || echo -n -e '  diff \033[0;31mNG\033[0;37m'

    if [ "$actual" = "$expected" ]; then
        echo -n -e '  status \033[0;32mOK\033[0;37m\n'
    else
        echo -n -e "  status \033[0;31mNG\033[0;37m, expected $expected but got $actual\n"
    fi
    echo 
    rm out cmp
}

#$
assert "echo $'test'"
assert "echo $"test""
assert "echo $HOME"
assert "echo '$HOME'"
assert "echo "$HOME""
assert "echo $NONEXITS"
assert "echo '$NONEXITS'"
assert "echo "$NONEXITS""
assert "echo test "$NONEXITS" test"
assert "echo test $NONEXITS test"

assert "echo test''test''test"
assert "echo $HOME$NONEXIT$HOME"
assert "echo "$HOME"test"
assert "echo '$HOME'test"
assert "echo "$HOME""$USER""
assert "echo "$HOME"'$USER'test"
assert "echo "$USER;test""
assert "echo ''"
assert "echo """
# assert "echo '"'"

# assert "echo '"'"'""
# assert "echo "'''''''''''""
assert "echo ''""""''"""
assert "echo '""""""""'"
assert "echo '"$test"$USER'"
assert "echo ""test"''test""
assert "'"
assert """"
assert "$NONEXITS"
# assert ""export SP=""a  b    c   ""
# echo $SP | cat -e
 # ""

# assert ""export SP=""a  b  a  ca a  ""
# export IFS=""a""
# echo $SP | cat -e
# ""
# assert ""export SP=""a  b  a  ca a  ""
# export IFS=""a""
# echo $SP | cat -e
# """
# "assert ""export QUOTE=""' '  ' ""
# echo $QUOTE | cat -e
# """
# "assert ""export QUOTE='"" ""   ""  '
# echo $QUOTE | cat -e
# """
# "assert ""export QUOTE='"" ""   '
# echo $QUOTE | cat -e
# """
# "assert ""export QUOTE=""   '   '      '    ' ""
# echo $QUOTE | cat -e
# """
# "assert ""export QUOTE=""   '   '      '    ' ""
# echo ""'$QUOTE' ' '"" | cat -e
# """
# "assert ""export SP=""a  b   ""
# < $SP
# """
assert ""< $UNEXITS
""
# assert "ls *txt"

# assert "ls tx*"
# assert "ls *****"
# assert "ls '*'*"
# assert "ls *'*'"
# assert "ls *'*'*"
# assert "ls *'*'"*"*"
# assert "ls *txt*"
# assert "ls *txt*txt"
# assert "ls txt*txt*txt"
# assert ""bash-5.2$ << eof cat
# assert ""bash-5.2$ << eof cat
# > '$USER'$"USER"
# > eof
# "
# "assert ""bash-5.2$ << eof cat
# > '""$HOME""' '$HOME
# > eof
# """
# "assert ""bash-5.2$ << eof cat
# > '$NONEXIT'
# > eof
# """
# "assert ""bash-5.2$ export QUOTE=""'   ' '  '  ""
# bash-5.2$ << eof cat
# > $QUOTE
# > eof
# """
# "assert ""bash-5.2$ export QUOTE=""'   '   '  ""
# bash-5.2$ << eof cat
# > '$QUOTE'
# > eof
# """

assert ""
assert "echo "$HOME"test"
assert "echo "$HOME""$USER""
assert "echo "$HOME"'$USER'test"
assert "echo "$USER;test""
# "assert ""export SP=""a  b   ""
# < $SP"""
# "assert ""bash-5.2$ export QUOTE=""'   '   '  ""
# bash-5.2$ <<eof cat
# > $QUOTE
# > eof"""
# "assert ""bash-5.2$ << eof cat
#   '$USER'$""USER""
# eof"""
