# minishell
A 42 project

# Used Functions

## readline

Readline é muito parecido com o get_next_line do libft
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>

int main(void)
{
    char    *prompt;
    char    *line;

    prompt = "Question: ";
    do
    {
        line = readline(prompt);
        if (!line)
            break ;
        printf("Answer: %s\n", line);
        free(line);
    } while (true);
    printf("\nEOF\n");
    return (0);
}
```
O programa deve ser compilado com a flag `-lreadline`
Este é o resultado
```console
$ clang readline.c -lreadline -o readline
$ ./readline
Question: 1 + 2
Answer: 1 + 2
Question: 3
Answer: 3
Question:
EOF
$
```

## rl_on_new_line

Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.

## rl_replace_line

Altera o conteúdo do rl_line_buffer e limpa o undo_list se o segundo argumento for diferente de zero

## rl_redisplay

Muda o conteúdo exibido na tela para o estado atual do rl_line_buffer

## add_history

adiciona linha ao histórico do console

```c
#include <readline/history.h>

    add_history(line);
```
## rl_clear_history

limpa o historico de linhas adicionado pelo add_history()

## printf
## malloc
## free
## write
## open
## read
## close
## fork
cria um novo processo filho
as variáveis do programa são compartilhadas até o momento do fork
returns
- -1 falhou em criar o processo
- 0 processo filho
- \>0 pid do processo filho

## wait
pid_t wait(int *exit_code);
wait espera um dos processsos filhos finalizar. retorna o pid do processo filho e o exit_code

## waitpid
espera por um processo em especifico
https://www.youtube.com/watch?v=kCGaRdArSnA

## wait3
## wait4
## signal
## kill
## exit
termina o programa com um código de saída

## getcwd
devolve o diretório atual do programa, precisa receber um monteiro e seu tamanho

## chdir
## stat
## lstat
## fstat
## unlink
## execve
## dup
cria uma copia de um file descriptor com menor fd disponivel

## dup2
cria uma copia de um file descriptor com o fd especificado
(se o fd especificado já estiver aberto, ele será fechado)

## pipe
abre dois file descriptors, o primeiro serve para leitura e o segundo para escrita
int fd[2];
pipe(fd);
retorna 0 se der certo e -1 se falhar

## opendir
abre um directory stream
https://www.youtube.com/watch?v=j9yL30R6npk

## readdir
devolve uma struct com informações sobre a entidade na pasta
- cada vez que é chamado devolve a próxima entidade

## closedir
fecha o directory stream de uma pasta

## strerror
devolve uma string com a descrição do erro da variavel errno
- não precisa dar free na string retornada
- a string pode mudar quando strerror for chamado outra vez

## perror
## isatty
## ttyname
## ttyslot
## ioctl
## getenv
## tcsetattr
## tcgetattr
## tgetent
## tgetflag
## tgetnum
## tgetstr
## tgoto
## tputs
