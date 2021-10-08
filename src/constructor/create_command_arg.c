/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:29:32 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 21:31:36 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_command_arg(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token		*token;
	t_command	*command;
	t_dlist		*node;

	if (!tokens)
		return (true);
	token = tokens->content;
	if (token->id != TD_WORD)
		return (false);
	command = ft_lstlast(*commands)->content;
	node = ft_dlstnew(ft_strdup(token->value));
	if (!node || !node->content)
		exit_minishell();
	ft_dlstadd_back(&(command->call.argv), node);
	return (create_command_arg(tokens->next, commands, operators)
		|| create_redirect(tokens->next, commands, operators)
		|| create_operator(tokens->next, commands, operators));
}
