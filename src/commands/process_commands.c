/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:10:22 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/16 16:07:13 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_commands(t_dlist *tokens)
{
	t_command	*command;
	int			*the_pipe;

	if (!tokens)
		return ;
	the_pipe = NULL;
	while (tokens)
	{
		command = get_next_command(&tokens);
		restore_std_fd();
		if (command->op == TD_PIPE)
			operator_pipe(&the_pipe, command);
		else if (!operator_conditional(&the_pipe, command))
			break ;
		command_free(command);
		command = NULL;
	}
	command_free(command);
	command = NULL;
	restore_std_fd();
	while (wait(NULL) != -1)
		;
}
