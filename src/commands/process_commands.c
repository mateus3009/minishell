/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:10:22 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/09 19:39:23 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_commands(t_dlist *tokens)
{
	t_command	*command;

	while (tokens)
	{
		command = get_next_command(&tokens);
		command_show(command);
		free(command);
	}
}
