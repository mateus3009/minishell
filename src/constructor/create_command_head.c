/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_head.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:29:09 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 21:31:55 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_command_head(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token		*token;
	t_command	*command;
	t_list		*node;

	if (!tokens)
		return (false);
	token = tokens->content;
	if (token->id != TD_WORD)
		return (false);
	command = ft_calloc(1, sizeof(t_command));
	command->call.path = find_command_path(
			find_env(g_minishell.penv, "PATH"), token->value);
	command->call.argv = ft_dlstnew(ft_strdup(token->value));
	node = ft_lstnew(command);
	if (!node || !node->content)
		exit_minishell();
	ft_lstadd_back(commands, node);
	return (create_command_arg(tokens->next, commands, operators)
		|| create_redirect(tokens->next, commands, operators)
		|| create_operator(tokens->next, commands, operators));
}

