/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_run_pipeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 07:44:33 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 22:48:43 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command(void *command)
{
	t_command	*c;

	c = command;
	free(c->call.path);
	ft_dlstclear(&c->call.argv, free);
	ft_dlstclear(&c->redirects, token_free);
	free(c);
}

void	create_and_run_pipeline(t_dlist *tokens)
{
	t_list	*commands;
	t_list	*operators;

	commands = NULL;
	operators = NULL;
	if (!tokens)
		return ;
	//if (!create_pipeline(tokens, &commands, &operators))
	//	exit_minishell();
	g_minishell.error_status = run_pipeline(commands, operators);
	ft_lstclear(&commands, free_command);
	ft_lstclear(&operators, free);
}
