#!/bin/bash

RESET="\033[0m"
RED="\033[31m"
GREEN="\033[32m"

UP="\033[A"
DOWN="\033[B"

ok=0
fail=0
index=0
pathscript=$(eval pwd)

function test()
{
	# Define variables
	((index=index+1))
	id=$index
	lines=("$@")
	failure=false

	# Create folder for the test
	mkdir -p tests
	cd tests && mkdir -p $id && cd $id

	# Write test file
	for l in "${lines[@]}"
	do
		echo $l >> "test_str"
	done

	# Run Minishell
	mkdir -p minishell && cd minishell
	$(eval "../../../minishell < ../test_str 2> /dev/null 1> out")
	minishell_exit_code=$?
	$(eval "ls | xargs -l bash -c 'sed -i s/minishell/terminal/g \$0'")
	$(eval "ls | xargs -l bash -c 'sed -i s/bash/terminal/g \$0'")
	cd ..

	# Run Bash
	mkdir -p bash && cd bash
	$(eval "bash < ../test_str 2> /dev/null 1> out")
	bash_exit_code=$?
	$(eval "ls | xargs -l bash -c 'sed -i s/minishell/terminal/g \$0'")
	$(eval "ls | xargs -l bash -c 'sed -i s/bash/terminal/g \$0'")
	cd ..

	# Check exit code
	if [ "$minishell_exit_code" != "$bash_exit_code" ]
	then
		echo -e "${RED}Exit code is different!${RESET} Bash: ${bash_exit_code}, Minishell: ${minishell_exit_code}"
		failure=true
	fi

	# Check files content
	if [ "$(ls bash | xargs -l bash -c 'diff bash/$0 minishell/$0' | wc -l)" != "0" ]
	then
		echo -e "${RED}The generated files content are different!${RESET}"
		failure=true
	fi

	# Check files quantity
	if [ "$(ls bash | wc -l)" != "$(ls minishell | wc -l)" ]
	then
		echo -e "${RED}The generated files quantity are different!${RESET}"
		failure=true
	fi

	# Check if has a failure
	if [ "$failure" = false ]
	then
		echo -e "${GREEN}Success!${RESET} id: ${id}"
		((ok=ok+1))
	else
		echo -e "${RED}Failure!${RESET} id: ${id}"
		((fail=fail+1))
	fi
	cd ../..
}

rm -rf  "tests"
rm failures

test "/bin/echo bonjour"
test "echo -n ola mundo"
test "echo \$HOME"
test "echo \"\$HOME\""
test "echo '\$HOME'"
test "echo '\$HO'ME"
test "echo \"\$HO\"ME"
test "ec\"ho\" uhu"
test "       ec\"ho\" uhu"
test ""
test "\"foo=bar\""
test "foo=bar echo \$foo"
test "foo=bar && echo \$foo"
test "pwd"
test "pwd foo bar"
test "cd"
test "cd -"
test "cd --" # está chamando o oldpwd
test "cd ~" # problema do ~
test "cd .."
test "cd ./"
test "cd ."
# test "." # vamos ver...
test "./"
test ".."
test "$"
test "$HOME"
test "echo $HOME > foo > bar"
test '<< teste cat 42 teste'
test '<< a << b << c << d'
test "/"
test "/bin"
test "/bin/"
test "/bin/cat"
test "/bin/cat < foo"
test "/bin/cat < foo < bar"
test " "
test '	'
test "> foo"
test "< foo"
test "< foo > bar"
test "> bar < foo"
test "exit | echo 42 > 42"
test "echo -n uhu"
test "echo -n uhu | echo -n uhu uh"
test "ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls"
test "pwd > a | grep /"
test "echo echo echo echo echo echo echo"
test "echo -n echo -n echo -n echo -n echo"
test "                                echo -n echo"
test "echo                       -n           echo"
test ""
test "<< teste cat" "ola 42" "teste"
test "export foo=bar bar=foo" "export bar" "export | sed s/=.*//" # é para mostrar o _ ou não?
# test "export | sed s/=.*//" # não está setando a variável _
test "export _" # segfault
test "export =" # segfault
test "export _=" # segfault
test "export =_" # segfault
test "export 12233" # segfault
test "export _12233" # segfault
test "export _a12233" # segfault
test "export a_a12233"
test "export =1" # segfault
test "export uhu" "export | sed s/=.*// | grep uhu" # não sei cade o erro
test "abc=cde foo=bar aga= echo teste bar=foo" "env | sed s/=.*// | sort" # mudar estratégias para testar env e export
test "echo \":: \$foo\" && foo=bar && echo \":: \$foo\"" "export | sed s/=.*//" # esquisito
test "abc=cde foo=bar aga= && echo teste bar=foo" "env | sed s/=.*// | sort" # mudar estratégias para testar env e export
test "unset"
test "unset =" # segfault
test "unset $" # segfault
test "unset 1e23432" # segfault
test "unset ~" "unset ." "unset _" "unset =" "unset foo=" "unset bar=foo" # segfault
test "<< teste cat" "ola mundo" "teste"
test "<< teste cat" "ola mundo" # heredoc não está contando a linhas gerais
test "<< foo << bar cat << a " "1" "foo" "2" "bar" "3" "a" # não está printando o ultimo heredoc
test "<< foo << bar cat << a " "1" "foo" "2" "bar" "3" # não está printando o ultimo heredoc
test "echo '\$HOME' > input1" "echo '\$USER' > input2" "cat < input1 < input2"
test "foobar" "foobar" "foobar" "foobar" "foobar" "foobar" "foobar" "foobar"
test "ls" "cd ~" "ls" "echo -n house" # problema do ~
test "exit"
test "exit" "echo uhu"
test "exit 0" "echo uhu"
test "exit 1" "echo uhu"
test "exit 1 1" "echo uhu"
test "exit 1 1 1" "echo uhu"
test "exit a" "echo uhu"
test "exit a a" "echo uhu"
test "exit a a a" "echo uhu"
test "exit 1 2 a" "echo uhu"
test "exit a a a" "echo uhu"
test "exit | exit | exit | exit | echo end" "echo hello"
test "echo teste | exit" "echo hello" # está saíndo depois da primeira linha
test "exit -" # exit code 2 e numeric argument required
test "exit -32768"
test "exit 32767"
test "exit -2147483648"
test "exit 2147483647"
test "exit -9223372036854775808"
test "exit 9223372036854775807"
test "e\"x\"i't'"
test "e\"x\"i't' 4"
test "env | sed s/=.*// | sort > e" "cat e" "env | sed s/=.*// | sort" # env está esquisito
test "env | env | env | env | sed s/=.*// | sort" # env está esquisito
test "env | env | env | echo e" # env está esquisito
test "env | grep foo" "export foo=bar" "env | grep foo" "export foo" "env | grep foo" # env está esquisito
test "env | grep foo" "export foo=bar" "env | grep foo" "export foo=" "env | grep foo" # env está esquisito
test "cd" "pwd" "cd .." "pwd"
test "cd" "pwd" "cd .." "pwd"
test "cd /bin" "pwd" "cd /tmp" "pwd" # dificil
test "cd \$HOME" "pwd"
test "cd " "cd ~" "cd ~/" # dificil
test "cd /bin" "pwd" "cd /tmp" "pwd" "unset HOME" "cd" "cd ~" # dificil ~
test "cd /bin" "pwd" "cd /tmp" "pwd" "unset OLDPWD" "cd - " # CD /BIN ESTÁ ESTRANHO...
test "cd /bin" "pwd" "cd /tmp" "pwd" "unset PWD" "pwd" "cd" "pwd" "cd -" "pwd" # CD /BIN ESTÁ ESTRANHO...
test "cd ]2" "cd @" "cd 21edsaa" "cd cd cd cd cd"
test "echo /bin > e" "cd < e" "pwd"
# test "pwd" "mkdir -p a/b/c" "cd a/b/c" "pwd" "rm -rf ../../" "cd .." "pwd" # exit code errado
test "cat bla"
test "echo $?"
test "foo='\$USE'" "bar=R" "echo \"\$foo\$bar\"" # var expansion
test "export ~" # SEGFALT
test "export \$foo=bar" "echo \$foo" # está exportando no parent e não no child
test "export foo=b\"a\"r\$USER\$foo" "echo \$foo" # está exportando no parent e não no child
test "export foo=bar | echo \$foo" # está exportando no parent e não no child
# test "export foo=bar | export bar=foo && echo \$foo \$bar" # está exportando no parent e não no child
test "\$HOME\$HOME\$HOME\$HOME"
# test "cat -e | cat -e | cat -e | cat" "<3" # dificil
test "cd ~" "ls | exit" # problema do ~
test "> a > b > c > d echo hello world" "cat < a < b < c < d"
test ">> a > b >> c > d echo hello worl" "cat < a < b < c < d"
test "echo hello world > e" "<< test cat < e >> a > b" "42" "test"
test "<< '\$HOME' cat >> e" "hello" # heredoc general line
test "<< '\$HOME' cat >> e << a" "hello" # heredoc general line
test "<< '\$HOME' cat >> e" "hello" "\$HOME"
test "<< '\$HOME' cat >> e << a" "hello" "\$HOME" "TEST" # heredoc general line
test "< dasdas grep"
test "echo teste > ." # deveria dar o erro: Is a directory (verificar permissões também!)
test "unset PATH" "cd"
test "unset PATH" "exit"
# test "unset PATH" "env" # isso deveria funcionar?
test "unset PATH" "export a"
test "unset PATH" "unset b"
test "unset PATH" "pwd"
test "unset PATH" "echo PATH"
test "unset PATH" "cat file" "grep something" "ls" # deveria dar o erro: No such file or directory
# test "a && b &&" "echo foo" # tolerável
# test "&& a && b" "echo foo" # tolerável
test "|| a || b" "echo foo"
test "|" "echo foo"
test "&&" "echo foo"
test "||" "echo foo"
test "echo test || echo foo" #  OR not working
test "cat file || echo foo"
test "unset ''" # segfault
test "echo 42" "'echo 42'" "\"echo 42\""
test "cat fileerr | wc" "cat fileerr | wc -l"
test "cd ~" "ls -la" # dificil ~
test "foo=bar | echo \$foo" # dificil variaveis estão sendo setadas dentro do pipe
test " cd ../../../../../../../../../../../../../../../../../../../../../../../../../" "pwd"
test "<< test cat > outfile < && echo teste" "uhu" "test" "echo test"
test "cat fdsfsf" "echo uhu" "pwd"
echo
echo "ok: ${ok} fail: ${fail}"
