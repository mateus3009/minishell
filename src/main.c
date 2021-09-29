/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/29 11:29:27 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_call
{
	char	*path;
	char	**argv;
	char	**env;
}	t_call;

typedef struct s_redirect
{
	int		type;
	char	*value;
}	t_redirect;

typedef struct s_command
{
	t_call		call;
	t_redirect	redirect;
}	t_command;

void	create_pipe(int	**fd)
{
	if (!fd)
		return ;
	*fd = malloc(sizeof(int) * 2);
	if (!fd)
		exit_minishell();
	if (pipe(*fd) == -1)
		exit_minishell();
}

void	free_pipe(int *fd)
{
	if (!fd)
		return ;
	close(fd[0]);
	close(fd[1]);
	free(fd);
}

void	configure_reader_pipe_and_free(int *fd)
{
	if (!fd)
		return ;
	dup2(fd[0], STDIN_FILENO);
	free_pipe(fd);
}

void	configure_writer_pipe_and_free(int *fd)
{
	if (!fd)
		return ;
	dup2(fd[1], STDOUT_FILENO);
	free_pipe(fd);
}

void	run_command(int *in, int *out, t_command *command)
{
	configure_reader_pipe_and_free(in);
	configure_writer_pipe_and_free(out);
	if (execve(command->call.path, command->call.argv, command->call.env) == -1)
		exit_minishell();
}

int	prepare_command(int *in, t_list *commands, t_list *operators);

int	prepare_next_command(
	pid_t pid,
	int *in,
	t_list *commands,
	t_list *operators)
{
	int	operator;
	int	exit_code;

	operator = TD_WORD;
	if (operators)
		operator = *(int *)operators->content;
	if (!commands->next && in)
		free_pipe(in);
	exit_code = 0;
	if (operator == TD_AND || operator == TD_OR || !commands->next)
		waitpid(pid, &exit_code, 0);
	if ((operator == TD_OR && !exit_code)
		|| (operator == TD_AND && exit_code) || !commands->next)
		return (exit_code);
	return (prepare_command(in, commands->next, operators->next));
}

int	prepare_command(int *in, t_list *commands, t_list *operators)
{
	int		*out;
	pid_t	pid;

	out = NULL;
	if (operators && *(int *)operators->content == TD_PIPE)
		create_pipe(&out);
	pid = fork();
	if (pid == -1)
		exit_minishell();
	if (pid == 0)
		run_command(in, out, commands->content);
	free_pipe(in);
	return (prepare_next_command(pid, out, commands, operators));
}

int	run_pipeline(t_list *commands, t_list *operators)
{
	return (prepare_command(NULL, commands, operators));
}

void	testinho(void)
{
	int			operator;
	t_command	a;
	t_command	b;
	t_list		*operators;
	t_list		*commands;

	operator = TD_PIPE;
	operators = NULL;
	ft_lstadd_back(&operators, ft_lstnew(&operator));
	a = (t_command){
		.call = (t_call){
			.path = "/bin/cat",
			.argv = (char *[]){"cat", "file.txt", NULL},
			.env = (char *[]){NULL}},
		.redirect = {0}};
	b = (t_command){
		.call = (t_call){
			.path = "/bin/grep",
			.argv = (char *[]){"grep", "42", NULL},
			.env = (char *[]){NULL}},
		.redirect = {0}};
	commands = NULL;
	ft_lstadd_back(&commands, ft_lstnew(&a));
	ft_lstadd_back(&commands, ft_lstnew(&b));
	run_pipeline(commands, operators);
	ft_lstclear(&operators, NULL);
	ft_lstclear(&commands, NULL);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_dlist	*tokens;

	testinho();
	exit(0);
	if (argc && argv)
		g_minishell.penv = parse_env(env);
	while (1)
	{
		tokens = NULL;
		read_input_and_save_history(&line);
		token_recognition(&tokens, line);
		parse(&tokens);
		ft_dlstclear(&tokens, token_free);
		free(line);
	}
	rl_clear_history();
	free_env(g_minishell.penv);
	return (0);
}
