/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:29:48 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 21:30:35 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_redirect(
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
	if (token->id != TD_INPUT && token->id != TD_OUTPUT
		&& token->id != TD_APPEND_MODE && token->id != TD_HERE_DOCUMENT)
		return (false);
	command = ft_lstlast(*commands)->content;
	node = ft_dlstnew(token_init(token->id, token->value));
	if (!node || !node->content)
		exit_minishell();
	ft_dlstadd_back(&(command->redirects), node);
	return (create_redirect(tokens->next, commands, operators)
		|| create_operator(tokens->next, commands, operators));
}
