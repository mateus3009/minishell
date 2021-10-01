/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 07:49:12 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 22:28:554 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	run_command(int *in, int *out, t_command *command)
{
	(void)in;
	(void)out;
	restore_std_fd();
	//configure_reader_pipe_and_free(in);
	//configure_writer_pipe_and_free(out);
	return (execute_command(command));
}

static int	prepare_command(int *in, t_list *commands, t_list *operators);

static int	prepare_next_command(
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
	if (pid && (operator == TD_AND || operator == TD_OR || !commands->next))
	{
		waitpid(pid, &exit_code, 0);
		if (WIFEXITED(exit_code))
			g_minishell.error_status = WEXITSTATUS(exit_code);
	}
	if ((operator == TD_OR && !exit_code)
		|| (operator == TD_AND && exit_code) || !commands->next)
		return (exit_code);
	return (prepare_command(in, commands->next, operators->next));
}

static int	prepare_command(int *in, t_list *commands, t_list *operators)
{
	int		*out;
	pid_t	pid;

	out = NULL;
	if (operators && *(int *)operators->content == TD_PIPE)
		create_pipe(&out);
	pid = run_command(in, out, commands->content);
	free_pipe(in);
	return (prepare_next_command(pid, out, commands, operators));
}

int	run_pipeline(t_list *commands, t_list *operators)
{
	return (prepare_command(NULL, commands, operators));
}
