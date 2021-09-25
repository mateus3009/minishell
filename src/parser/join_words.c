/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:42:00 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/25 10:42:37 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		add_token_to_result(tokens, TD_WORD, (*builder)->str);
		str_builder_destroy(*builder);
		*builder = NULL;
	}
	add_token_to_result(tokens, token->id, token->value);
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
		add_token_to_result(&new_tokens, TD_WORD, builder->str);
		str_builder_destroy(builder);
	}
	ft_dlstclear(ptr_tokens, token_free);
	*ptr_tokens = new_tokens;
}
