/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:30:03 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 21:31:19 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_operator(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token	*token;
	int		*number;
	t_list	*node;

	if (!tokens)
		return (true);
	token = tokens->content;
	if (token->id != TD_PIPE && token->id != TD_AND && token->id != TD_OR)
		return (false);
	number = malloc(sizeof(int));
	if (!number)
		exit_minishell();
	*number = token->id;
	node = ft_lstnew(number);
	if (!node)
		exit_minishell();
	ft_lstadd_back(operators, node);
	return (create_command_head(tokens->next, commands, operators));
}
