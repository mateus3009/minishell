/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 13:33:37 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/10 18:21:09 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	operator_conditional(int **input, t_command *command)
{
	pid_t	pid;
	int		exit_code;

	restore_std_fd();
	pid = fork();
	if (pid == -1)
		exit_minishell();
	if (pid == 0)
	{
		pipe_set_reader(*input);
		configure_redirect(command);
	}
	pipe_free(*input);
	*input = NULL;
	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
		g_minishell.error_status = WEXITSTATUS(exit_code);
	if (WIFSIGNALED(exit_code))
		g_minishell.error_status = WTERMSIG(exit_code);
	if (command->op == TD_OR)
		return (g_minishell.error_status);
	return (g_minishell.error_status == 0);
}

bool	operator_pipe(int **input, t_command *command)
{
	int		*ouput;
	pid_t	pid;

	restore_std_fd();
	ouput = pipe_create();
	pid = fork();
	if (pid == -1)
		exit_minishell();
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
