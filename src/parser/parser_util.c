/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 22:24:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/06 23:37:43 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
t_dlist	*next_word_token(t_dlist *token)
{
	t_token *t;

	if (!token || !token->next)
		return (NULL);
	token = token->next;
	t = token->content;
	if (t->id == TD_SPACE)
	{
		token = token->next;
		t = token->content;
	}
	if (t->id != TD_WORD)
		return (NULL);
	return (token);
}

t_token	*previous_token_non_space(t_dlist *token)
{
	t_token	*t;

	if (!token || !token->previous)
		return (NULL);
	token = token->previous;
	t = token->content;
	if (t->id == TD_SPACE)
	{
		token = token->previous;
		t = token->content;
	}
	return (t);
}
*/
