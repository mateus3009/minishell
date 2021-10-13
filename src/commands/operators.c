/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 13:33:37 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/12 18:54:35 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_pid_and_set_status(pid_t pid)
{
	int	exit_status;

	if (pid == 0)
		return (g_minishell.error_status);
	waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		g_minishell.error_status = WEXITSTATUS(exit_status);
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status))
			ft_putendl_fd("Segmentation fault", STDERR_FILENO);
		g_minishell.error_status = 128 + WTERMSIG(exit_status);
	}
	return (g_minishell.error_status);
}

bool	operator_conditional(int **input, t_command *command)
{
	pid_t	pid;

	pipe_set_reader(*input);
	pid = configure_redirect(command);
	*input = NULL;
	wait_pid_and_set_status(pid);
	if (command->op == TD_OR)
		return (g_minishell.error_status);
	return (g_minishell.error_status == 0);
}

bool	operator_pipe(int **input, t_command *command)
{
	int		*ouput;
	pid_t	pid;

	ouput = pipe_create();
	pid = fork();
	if (pid == -1)
		exit_minishell();
	set_exec_signals();
	if (pid == 0)
	{
		pipe_set_reader(*input);
		pipe_set_writer(ouput);
		configure_redirect(command);
	}
	pipe_free(*input);
	*input = ouput;
	return (true);
}
