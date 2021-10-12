/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:10:22 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/12 17:06:05 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_commands(t_dlist *tokens)
{
	t_command	*command;
	int			*the_pipe;

	the_pipe = NULL;
	while (tokens)
	{
		command = get_next_command(&tokens);
		//command_show(command);
		restore_std_fd();
		if (command->op == TD_PIPE)
			operator_pipe(&the_pipe, command);
		else
			operator_conditional(&the_pipe, command);
		command_free(command);
		command = NULL;
	}
	restore_std_fd();
	while (wait(NULL) != -1)
		;
}
