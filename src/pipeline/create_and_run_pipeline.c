/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_run_pipeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 07:44:33 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 08:01:52 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command(void *command)
{
	t_command	*c;

	c = command;
	free(c->call.path);
	free(c->call.argv);
	free(c->call.env);
	free(c->redirect.value);
	free(c);
}

void	create_and_run_pipeline(t_dlist *tokens)
{
	t_list	*commands;
	t_list	*operators;

	commands = NULL;
	operators = NULL;
	if (!create_pipeline(tokens, &commands, &operators))
		exit_minishell();
	g_minishell.error_status = run_pipeline(commands, operators);
	ft_lstclear(&commands, free_command);
	ft_lstclear(&operators, free);
}
