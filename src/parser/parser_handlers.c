/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:31:14 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/09 11:53:58 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	local_variables_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;
	t_dlist	*bar;
	t_dlist *foo;
	char	*value;

	token = (*tokens)->content;
	if (token->id != TD_WORD || !ft_isalpha(*token->value)
		|| !ft_strchr(token->value, '='))
		return (false);
	bar = previous_token(ft_dlstlast(*new));
	if (bar && ((t_token *)bar->content)->id != TD_VARIABLE)
		return (false);
	foo = *tokens;
	value = join_words(&foo);
	if (!value)
		return (false);
	add_token_to_result(new, TD_VARIABLE, value);
	*tokens = foo;
	return (true);
}

bool	space_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;

	token = (*tokens)->content;
	if (!new || token->id != TD_SPACE)
		return (false);
	*tokens = (*tokens)->next;
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
	temp = next_token(*tokens);
	if (!temp)
		return (false);
	next = temp->content;
	add_token_to_result(new, token->id, token->value);
	*tokens = temp->next;
	return (true);
}

int	common_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;

	token = (*tokens)->content;
	if (token->id == TD_UNKNOWN)
		return (-1);
	add_token_to_result(new, token->id, token->value);
	*tokens = (*tokens)->next;
	return (1);
}
