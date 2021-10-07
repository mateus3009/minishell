/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:31:14 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/06 23:37:33 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
bool	local_variables_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;
	t_token *temp;
	char	*value;

	token = (*tokens)->content;
	if (token->id != TD_WORD || !ft_isalpha(*token->value)
		|| !ft_strchr(token->value, '='))
		return (false);
	temp = previous_token_non_space(token);
	if (temp && temp->id != TD_VARIABLE)
		return (false);
	temp = (*tokens)->next;
	value = join_words(&temp);
	if (!value)
		return (false);
	ft_dlstadd_back(new, ft_dlstnew(token_init(TD_VARIABLE, value)));
	*tokens = temp;
	return (true);
}

bool	redirects_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;
	t_dlist	*temp;
	t_token	*next;

	token = (*tokens)->content;
	if (token->id != TD_INPUT && token->id != TD_OUTPUT
		&& token->id != TD_APPEND_MODE)
		return (false);
	temp = next_word_token(*tokens);
	next = temp->content;
	ft_dlstadd_back(new, ft_dlstnew(token_init(token->id, next->value)));
	*tokens = temp;
	return (true);
}

bool	space_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;

	token = (*tokens)->content;
	if (token->id != TD_SPACE)
		return (false);
	*tokens = (*tokens)->next;
	return (true);
}
*/
