#!/bin/bash

CLEAR="\033[0m"
BOLD="\033[1m"
ULINE="\033[4m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"

# SHELL=../minishell_test
SHELL=../minishell
MINISHELL_LOG_DIR=minishell
TEST_SHELL=bash
OUTPUT_FILE=RESULT_LOG
OUT_FILE_MINISHELL=output_file_minishell.txt
OUT_FILE_BASH=output_file_bash.txt
LEAK_TEST_FILE=leak_test_file
OK=[OK]
NG=[NG]

print_ok() {
		COLOR=${GREEN}
		printf "	${COLOR}${OK}${CLEAR}"
}

print_ko() {
		COLOR=${RED}
		printf "	${COLOR}${NG}${CLEAR}"
}

remove_output_files() {
	rm -rf ${OUTPUT_FILE} ${OUTPUT_FILE}
	rm -rf ${OUT_FILE_MINISHELL} ${OUT_FILE_BASH}
	rm -rf ${LEAK_TEST_FILE}
}

# インファイルで行えるテストを実行する関数
test_infile() {

	file_list=$(ls -1 ${1}/*test.txt 2> /dev/null)
	if [[ $? -ne 0 ]]; then
		printf "${BOLD}${RED}${1}をテストするファイルが存在しませんでした。${CLEAR}\n\n"
		return 0
	fi
	file_count=$(echo "${file_list}" | wc -l)

	printf "${YELLOW}${BOLD}${ULINE}# ${1}_test ${CLEAR}: \n"

	for i in $(seq 1 ${file_count})
	do
		# input_file=${1}/*$itest.txtにすれば自由度は高まるが一意にならないため好ましくないかも
		input_file=${1}/${i}test.txt
		output_file_minishell=${OUTPUT_FILE}/${1}/${MINISHELL_LOG_DIR}_${i}.txt
		output_file_bash=${OUTPUT_FILE}/${1}/${TEST_SHELL}_${i}.txt
		stderr_file_minishell=${OUTPUT_FILE}/${1}/${MINISHELL_LOG_DIR}_${i}_stderr.txt
		stderr_file_bash=${OUTPUT_FILE}/${1}/${TEST_SHELL}_${i}_stderr.txt

		mkdir -p ${OUTPUT_FILE}/${1}

		printf "${ULINE}# ${input_file} ${CLEAR}: \n"

		# 自作のシェルを起動し、${input_file}の内容を実行します
		${SHELL} < ${input_file} > ${output_file_minishell} 2> ${stderr_file_minishell}
		ret1=$?

		${TEST_SHELL} --norc -i < ${input_file} 2>&1 > ${output_file_bash} | grep -v "no job control in this shell" | grep -v "cannot set terminal process group" > ${stderr_file_bash}
		ret2=${PIPESTATUS[0]}

		# 出力が期待通りであることを確認
		df=$(diff -q ${output_file_minishell} ${output_file_bash})
		df_err=$(diff -q ${stderr_file_minishell} ${stderr_file_bash})

		if [ "$df" = "" ] && ( [ "$1" = "command" ] || [ "$df_err" = "" ] ) && [[ ${ret1} -eq ${ret2} ]]; then
			print_ok
		else
			print_ko
			echo "exit status : " $ret1 $ret2

			echo
			echo stdout minishell
			cat ${output_file_minishell}
			echo
			echo stdout bash
			cat ${output_file_bash}

			echo
			echo stderr minishell
			cat ${stderr_file_minishell}
			echo
			echo stderr bash
			cat ${stderr_file_bash}

			return 1
		fi
		printf "  ${SHELL} < ${input_file} > ${output_file_minishell}\n  ${TEST_SHELL} < ${input_file} > ${output_file_bash}\n"
		printf "\n\n"

	done
	return 0
}

# アウトファイルのリダイレクションテストを実行する関数
test_redirect() {

	file_list=$(ls -1 ${1}/*_minishell_test.txt 2> /dev/null)
	if [[ $? -ne 0 ]]; then
		printf "${BOLD}${RED}${1}をテストするファイルが存在しませんでした。${CLEAR}\n\n"
		return 0
	fi
	file_count=$(echo "${file_list}" | wc -l)

	printf "${YELLOW}${BOLD}${ULINE}# ${1}_test ${CLEAR}: \n"

	for i in $(seq 1 ${file_count})
	do
		redirect_file_minishell=${1}/${i}_minishell_test.txt
		redirect_file_bash=${1}/${i}_bash_test.txt

		printf "${ULINE}# ${redirect_file_minishell} | ${redirect_file_bash} ${CLEAR}: "

		# 自作のシェルを起動し、${input_file}の内容を実行します
		${SHELL} < ${redirect_file_minishell}
		ret1=$?

		${TEST_SHELL} < ${redirect_file_bash}
		ret2=$?

		# 出力が期待通りであることを確認
		df=$(diff -q ${OUT_FILE_MINISHELL} ${OUT_FILE_BASH})

		echo "exit status : " $ret1 $ret2

		if [ "$df" = "" ] && [[ ${ret1} -eq ${ret2} ]]; then
			print_ok
		else
			print_ko
			return 1
		fi
		printf "  ${SHELL} < ${redirect_file_minishell}\n  ${TEST_SHELL} < ${redirect_file_bash}\n"
		printf "\n\n"

	done
	return 0
}

# リークテストを行う
test_leak_infile() {

	file_list=$(ls -1 ${1}/*test.txt 2> /dev/null)
	if [[ $? -ne 0 ]]; then
		printf "${BOLD}${RED}${1}をテストするファイルが存在しませんでした。${CLEAR}\n\n"
		return 0
	fi
	file_count=$(echo "${file_list}" | wc -l)

    printf "${YELLOW}${BOLD}${ULINE}# ${1}_leak_test ${CLEAR}: \n"

    	threshold=10

	if [ $file_count -ge $threshold ]; then

		RANDOM=$$
		test_num=$threshold

		for i in $(seq 1 ${test_num})
		do
			input_file=${1}/$(( RANDOM % file_count + 1 ))test.txt

			printf "${ULINE}# ${input_file}: "

			valgrind ${SHELL} < ${input_file} > ${LEAK_TEST_FILE} 2>&1
			cat ${LEAK_TEST_FILE} | grep -q "definitely lost: 0 bytes in 0 blocks"

			if [ $? -eq 0 ]; then
				print_ok
			else
				print_ko
				return 1
			fi

			printf "  valgrind ${SHELL} < ${input_file} > ${LEAK_TEST_FILE} 2>&1
					cat ${LEAK_TEST_FILE} | grep -q "definitely lost: 0 bytes in 0 blocks"\n"
			rm ${LEAK_TEST_FILE}

			printf "\n\n"
		done
	else

		for i in $(seq 1 ${file_count})
		do
			input_file=${1}/${i}test.txt

			printf "${ULINE}# ${input_file}: "

			valgrind ${SHELL} < ${input_file} > ${LEAK_TEST_FILE} 2>&1
			cat ${LEAK_TEST_FILE} | grep -q "definitely lost: 0 bytes in 0 blocks"

			if [ $? -eq 0 ]; then
				print_ok
			else
				print_ko
				return 1
			fi

			printf "  valgrind ${SHELL} < ${input_file} > ${LEAK_TEST_FILE} 2>&1
					cat ${LEAK_TEST_FILE} | grep -q "definitely lost: 0 bytes in 0 blocks"\n"
			rm ${LEAK_TEST_FILE}

			printf "\n\n"
		done
	fi

	return 0
}

test_leak_redirect() {

	file_list=$(ls -1 ${1}/*_minishell_test.txt 2> /dev/null)
	if [[ $? -ne 0 ]]; then
		printf "${BOLD}${RED}${1}をテストするファイルが存在しませんでした。${CLEAR}\n\n"
		return 0
	fi
	file_count=$(echo "${file_list}" | wc -l)

    printf "${YELLOW}${BOLD}${ULINE}# ${1}_leak_test ${CLEAR}: \n"

	for i in $(seq 1 ${file_count})
	do
		input_file=${1}/${i}_minishell_test.txt

		printf "${ULINE}# ${input_file}: "

		valgrind ${SHELL} < ${input_file} > ${LEAK_TEST_FILE} 2>&1
		cat ${LEAK_TEST_FILE} | grep -q "definitely lost: 0 bytes in 0 blocks"

		if [ $? -eq 0 ]; then
			print_ok
		else
			print_ko
			return 1
		fi

		printf "  valgrind ${SHELL} < ${input_file} > ${LEAK_TEST_FILE} 2>&1
				cat ${LEAK_TEST_FILE} | grep -q "definitely lost: 0 bytes in 0 blocks"\n"
		rm ${LEAK_TEST_FILE}

		printf "\n\n"
	done
	return 0
}
main() {

	# テストタイプを配列に格納
	# test_types=("input" "heredoc" "command" "builtin" "pipe" "and" "or" "wildcard" "mix" "exit"
	# 			"cd" "unset" "export" "env" "echo" "pwd" "expansion")
	test_types=("input" "heredoc" "command" "builtin" "pipe" "and" "or" "wildcard" "mix" "exit"
				"cd" "unset" "export" "env" "echo" "pwd" "expansion")
	redirect_tests=("output" "add_output")
	# only status check ??? "syntax" "order"

	# シェル実行時に"rm"の引数があれば実行
	if [[ ${1} == "rm" ]]; then
		printf "${OUTPUT_FILE}の中身を削除します。\n"
		remove_output_files
		return
	fi

	printf "  ${BLUE}${BOLD}minishell test${CLEAR}\n\n"
	mkdir -p ${OUTPUT_FILE}

	# 引数が存在する場合、それを新たなテストタイプとして設定
	if [ $# -gt 0 ]; then
		copy_test_types=("${test_types[@]}")
		copy_redirect_tests=("${redirect_tests[@]}")
		test_types=()
		redirect_tests=()
		for arg in "$@"; do
			if [[ " ${copy_test_types[*]} " == *" $arg "* ]]; then
				test_types+=("$arg")
			elif [[ " ${copy_redirect_tests[*]} " == *" $arg "* ]]; then
				redirect_tests+=("$arg")
			else
				printf "Error: Argument '%s' is an unrecognized test type.\n" "$arg"
				return 1
			fi
		done
	fi

	# test_infile関数を各テストタイプに対して実行
	for test in "${test_types[@]}"; do
		test_infile "$test"
		ret=$?
		if [[ ret -ne 0 ]]; then
			printf "${test} failed !\n"
			return 1
		fi
	done

	# test_redirect関数を各テストタイプに対して実行
	for test in "${redirect_tests[@]}"; do
		test_redirect "$test"
		ret=$?
		if [[ ret -ne 0 ]]; then
			printf "${test} failed !\n"
			return 1
		fi
	done

	# リークテストを行う
	# 以下のif文をつけると、macOS以外で処理が動くようになる
	# if [[ $(uname) != Darwin ]]; then
		for test in "${test_types[@]}"; do
			test_leak_infile "$test"
			ret=$?
			if [[ ret -ne 0 ]]; then
				printf "${test} failed !\n"
				return 1
			fi
		done
		for test in "${redirect_tests[@]}"; do
			test_leak_redirect "$test"
			ret=$?
			if [[ ret -ne 0 ]]; then
				printf "${test} failed !\n"
				return 1
			fi
		done
	# fi

	return 0
}

# main関数を呼び出す
main "$@"


#使用方法
#・各ディレクトリに"数字test.txt"の形式でテストケースを追加する
#・./unit_test.sh ですべてのディレクトリにあるテストが実行される
#・./unit_test.sh に引数を与えると与えた引数のみテストを行う
#・"rm"の引数でテスト結果を削除できる
#注意点
#・out_fileのリダイレクションテストは、テストケースの出力ファイル名を固定にする必要がある
#・out_fileのリダイレクションテストは、2ファイル用意する必要がある


# 相談事項
#	outputredirectのテストの仕方、ファイルは固定になるためテストケースを書くファイルも気を付ける必要がある
#

#TODO:orderのディレクトリを作成しサンプルを置く
