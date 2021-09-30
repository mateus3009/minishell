/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:42:00 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/29 20:07:43 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_new_token(
	t_dlist **tokens,
	int id,
	char *str)
{
	t_token	*token;
	t_dlist	*node;

	if (id == TD_WORD && !str)
		return ;
	token = token_init(id, str);
	node = ft_dlstnew(token);
	if (!token || !node)
		exit(EXIT_FAILURE);
	ft_dlstadd_back(tokens, node);
}

static void	join_word_node(
	t_dlist **tokens,
	t_token *token,
	t_str_builder **builder)
{
	if (token->id == TD_WORD || token->id == TD_SINGLE_QUOTE
		|| token->id == TD_DOUBLE_QUOTE)
	{
		if (!*builder)
			*builder = str_builder_init();
		str_builder_add_str(*builder, token->value);
		return ;
	}
	if (*builder)
	{
		add_new_token(tokens, TD_WORD, (*builder)->str);
		str_builder_destroy(*builder);
		*builder = NULL;
	}
	if (token->id != TD_SPACE)
		add_new_token(tokens, token->id, token->value);
}

void	join_word(t_dlist **ptr_tokens)
{
	t_dlist			*tokens;
	t_dlist			*new_tokens;
	t_str_builder	*builder;

	tokens = *ptr_tokens;
	new_tokens = NULL;
	builder = NULL;
	while (tokens)
	{
		join_word_node(&new_tokens, tokens->content, &builder);
		tokens = tokens->next;
	}
	if (builder)
	{
		add_new_token(&new_tokens, TD_WORD, builder->str);
		str_builder_destroy(builder);
	}
	ft_dlstclear(ptr_tokens, token_free);
	*ptr_tokens = new_tokens;
}
