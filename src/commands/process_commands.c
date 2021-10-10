/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:10:22 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/10 14:34:58 by msales-a         ###   ########.fr       */
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
		if (command->op == TD_PIPE)
			operator_pipe(&the_pipe, command);
		else
			operator_conditional(&the_pipe, command);
		free(command);
	}
	while (wait(NULL) != -1)
		;
}
