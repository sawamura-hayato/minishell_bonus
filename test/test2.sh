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
assert "ls"
assert "ls -l"
assert "cat Makefile"
