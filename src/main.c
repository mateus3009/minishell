/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 07:30:29 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_call
{
	char	*path;
	t_dlist	*argv;
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

char	**compile_argv(t_dlist *args)
{
	size_t	len;
	char	**result;
	size_t	index;

	len = ft_dlstsize(args);
	result = malloc(sizeof(char *) * (len + 1));
	result[len] = NULL;
	index = 0;
	while (args)
	{
		result[index] = ft_strdup(args->content);
		index++;
		args = args->next;
	}
	return (result);
}

void	run_command(int *in, int *out, t_command *command)
{
	char	**argv;
	char	**env;

	configure_reader_pipe_and_free(in);
	configure_writer_pipe_and_free(out);
	argv = compile_argv(command->call.argv);
	env = tpenv_to_array(g_minishell.penv);
	if (execve(command->call.path, argv, env) == -1)
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

bool	create_command_head(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators);

bool	create_command_arg(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators);

bool	create_redirect(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators);

bool	create_operator(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators);

bool	create_command_head(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token		*token;
	t_command	*command;
	t_list		*node;
	char		*value;

	if (!tokens)
		return (false);
	token = tokens->content;
	if (token->id != TD_WORD)
		return (false);
	command = ft_calloc(1, sizeof(t_command));
	command->call.path = find_command_path(
		find_env(g_minishell.penv, "PATH"), token->value);
	value = ft_strdup(token->value);
	command->call.argv = ft_dlstnew(value);
	node = ft_lstnew(command);
	if (!node)
		exit_minishell();
	ft_lstadd_back(commands, node);
	return (create_command_arg(tokens->next, commands, operators)
		|| create_redirect(tokens->next, commands, operators)
		|| create_operator(tokens->next, commands, operators));
}

bool	create_command_arg(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token		*token;
	t_command	*command;
	t_dlist		*node;

	if (!tokens)
		return (true);
	token = tokens->content;
	if (token->id != TD_WORD)
		return (false);
	command = ft_lstlast(*commands)->content;
	node = ft_dlstnew(ft_strdup(token->value));
	if (!node)
		exit_minishell();
	ft_dlstadd_back(&(command->call.argv), node);
	return (create_command_arg(tokens->next, commands, operators)
		|| create_redirect(tokens->next, commands, operators)
		|| create_operator(tokens->next, commands, operators));
}

bool	create_redirect(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token		*token;
	t_command	*command;

	if (!tokens)
		return (true);
	token = tokens->content;
	if (token->id != TD_INPUT && token->id != TD_OUTPUT
		&& token->id != TD_APPEND_MODE && token->id != TD_HERE_DOCUMENT)
		return (false);
	command = ft_lstlast(*commands)->content;
	command->redirect.type = token->id;
	command->redirect.value = ft_strdup(token->value);
	return (create_operator(tokens->next, commands, operators));
}

bool	create_operator(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token	*token;
	int		*number;
	t_list	*node;

	if (!tokens)
		return (true);
	token = tokens->content;
	if (token->id != TD_PIPE && token->id != TD_AND	&& token->id != TD_OR)
		return (false);
	number = malloc(sizeof(int));
	if (!number)
		exit_minishell();
	*number = token->id;
	node = ft_lstnew(number);
	if (!number)
		exit_minishell();
	ft_lstadd_back(operators, node);
	return (create_command_head(tokens->next, commands, operators));
}

void	free_command(void *command)
{
	t_command *c;

	c = command;
	free(c->call.path);
	free(c->call.argv);
	free(c->call.env);
	free(c->redirect.value);
	free(c);
}

void	create_and_run_pipeline(t_dlist *tokens)
{
	t_list	*commands;
	t_list	*operators;

	commands = NULL;
	operators = NULL;
	if (!create_command_head(tokens, &commands, &operators))
		exit_minishell();
	g_minishell.error_status = run_pipeline(commands, operators);
	ft_lstclear(&commands, free_command); // TODO criar uma funcao de free
	ft_lstclear(&operators, free);
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
			.path = "/bin/echo",
			.argv = ft_dlstparray((char *[]){"echo", "teste\n42 bola\ncasa", NULL}, sizeof(char *), 3),
			.env = (char *[]){NULL}},
		.redirect = {0}};
	b = (t_command){
		.call = (t_call){
			.path = "/bin/grep",
			.argv = ft_dlstparray((char *[]){"grep", "42", NULL}, sizeof(char *), 3),
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

	if (argc && argv)
		g_minishell.penv = parse_env(env);
	while (1)
	{
		tokens = NULL;
		read_input_and_save_history(&line);
		token_recognition(&tokens, line);
		parse(&tokens);
		create_and_run_pipeline(tokens);
		ft_dlstclear(&tokens, token_free);
		free(line);
	}
	rl_clear_history();
	free_env(g_minishell.penv);
	return (0);
}
