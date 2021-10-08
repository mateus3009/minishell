/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:42:00 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 13:41:34 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_words(t_dlist **tokens)
{
	t_token			*token;
	t_str_builder	*builder;
	char			*result;

	if (!tokens || !*tokens)
		return (NULL);
	token = (*tokens)->content;
	builder = NULL;
	while (token->id == TD_WORD || token->id == TD_SINGLE_QUOTE
		|| token->id == TD_DOUBLE_QUOTE)
	{
		if (!builder)
			builder = str_builder_init();
		str_builder_add_str(builder, token->value);
		*tokens = (*tokens)->next;
		if (!*tokens)
			break ;
		token = (*tokens)->content;
	}
	if (builder)
	{
		result = ft_strdup(builder->str);
		str_builder_destroy(builder);
		return (result);
	}
	return (NULL);
}

bool	word_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;
	char	*value;

	token = (*tokens)->content;
	if (token->id != TD_WORD && token->id != TD_SINGLE_QUOTE
		&& token->id != TD_DOUBLE_QUOTE)
		return (false);
	value = join_words(tokens);
	ft_dlstadd_back(new, ft_dlstnew(token_init(TD_WORD, value)));
	return (true);
}
