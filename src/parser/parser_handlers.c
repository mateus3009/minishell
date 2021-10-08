/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:31:14 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 20:37:05 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	local_variables_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;
	t_token	*bar;
	t_dlist *foo;
	char	*value;

	token = (*tokens)->content;
	if (token->id != TD_WORD || !ft_isalpha(*token->value)
		|| !ft_strchr(token->value, '='))
		return (false);
	bar = previous_token_non_space(ft_dlstlast(*new));
	if (bar && bar->id != TD_VARIABLE)
		return (false);
	foo = *tokens;
	value = join_words(&foo);
	if (!value)
		return (false);
	ft_dlstadd_back(new, ft_dlstnew(token_init(TD_VARIABLE, value)));
	*tokens = foo;
	return (true);
}


bool	here_document_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;
	t_dlist	*temp;
	char	*value;

	token = (*tokens)->content;
	if (token->id != TD_HERE_DOCUMENT)
		return (false);
	temp = (*tokens)->next;
	temp = next_word_token(temp);
	value = join_words(&temp);
	if (!value)
		return (false);
	*tokens = temp;
	ft_dlstadd_back(new, ft_dlstnew(token_init(TD_HERE_DOCUMENT, value)));
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
	temp = next_word_token(*tokens);
	if (!temp)
		return (false);
	next = temp->content;
	ft_dlstadd_back(new, ft_dlstnew(token_init(token->id, next->value)));
	*tokens = temp->next;
	return (true);
}
