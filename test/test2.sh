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
assert "unset PATH"
assert "unset OLDPWD"
assert "unset PWD"
assert "unset $PATH"
assert "unset $OLDPWD"
assert "unset $PWD"
assert "ls"
assert "/bin/ls"
assert "ls a"
assert "ls Makefile"

assert "/bin/cat Makefile"
assert "cat Makefile"


#exit
assert "exit"
assert "eXiT"
assert "exit 3"
assert "exit 3 66"
assert "exit a b cc"
assert "exit | exit"
assert "exit 3 | exit 5"
assert "exit 3 5 | exit 2"

#echo
assert "echo"
assert "echo -n"
assert "echo -n----n-n"
assert "echo ----n-n"
assert "echo abc def"
assert "echo -n abc def"

#cd
assert "cd"
assert "cd -"
assert "cd /"
assert "cd ./../"
assert "cd ../../../"
assert "cd echo"
assert "cd *"
assert "cd \"*\""
assert "cd $A"
assert "cd c a d e"
assert "cd \'$A\'"
assert "cd \"$A\""

#pwd
assert "pwd"
assert "pwd a "
assert "pwd a v\""
assert "pwd \'$A\'"
assert "pwd \"$A\""

#export
assert "export"
assert "export a=R "
assert "export | grep a="
assert "export v\""
assert "export | grep v"
assert "export \'$a\'"
assert "export \"$a\"=vv"
assert "export | a="
assert "export | grep a="

#unset
assert "unset"
assert "unset a=R"
assert "unset | grep a="
assert "unset a=R"
assert "unset v\""
assert "unset | grep v"
assert "unset \'$a\'"
assert "unset \"$a\"=vv"
assert "unset | a="
assert "unset | grep a="

#env
assert "env"
assert "env a=R"
assert "env | grep a="
assert "env a=R"
assert "env v\""
assert "env | grep v"
assert "env \'$a\'"
assert "env \"$a\"=vv"
assert "env | a="
assert "env | grep a="

