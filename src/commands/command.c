/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:29:28 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/13 14:01:07 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(t_command *command)
{
	if (!command)
		return ;
	ft_dlstclear(&(command->words), free);
	ft_dlstclear(&(command->variables), free);
	ft_dlstclear(&(command->redirects), token_free);
	free(command);
}

t_command	*command_init(void)
{
	return (ft_calloc(1, sizeof(t_command)));
}
