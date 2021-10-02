/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:28:08 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/02 13:56:24 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	configure_and_run_redirect(int *p, t_command *command)
{
	if (command->redirect.type == TD_INPUT
		|| command->redirect.type == TD_HERE_DOCUMENT)
		configure_writer_pipe(p);
	else
		configure_reader_pipe(p);
	free_pipe(p);
	execute_redirect(command->redirect);
}*/

static void	configure_and_run_call(int *p, t_command *command)
{
	if (command->redirect.type == TD_INPUT
		|| command->redirect.type == TD_HERE_DOCUMENT)
		configure_reader_pipe(p);
	else
		configure_writer_pipe(p);
	free_pipe(p);
	execute_call(command->call);
}

void	execute_command(t_command *command)
{
	int		*p;

	p = NULL;
	/*
	pid_t	child;

	if (command->redirect.type)
	{
		create_pipe(&p);
		child = fork();
		if (child == -1)
			exit_minishell();
		if (child == 0)
			configure_and_run_redirect(p, command);
	}*/
	return (configure_and_run_call(p, command));
}
