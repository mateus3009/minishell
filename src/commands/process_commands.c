/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:10:22 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/17 12:46:08 by msales-a         ###   ########.fr       */
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
		null_std_fd();
		command = get_next_command(&tokens);
		if (command->op == TD_PIPE)
			operator_pipe(&the_pipe, command);
		else if (!operator_conditional(&the_pipe, command))
			break ;
		command_free(command);
		command = NULL;
	}
	command_free(command);
	command = NULL;
	while (wait(NULL) != -1)
		;
	restore_std_fd();
}
