/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:33:24 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/19 18:11:25 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_recognition_handler(
	t_dlist **tokens,
	t_token_builder *token,
	char *str,
	int *index)
{
	int	id;

	id = find_end_of_token(str, index, token);
	if (id != TD_WORD)
	{
		add_token_to_result(tokens, token->id, token->builder->str);
		if (id != token->id && id != TD_SINGLE_QUOTE
			&& id != TD_DOUBLE_QUOTE)
		{
			add_token_to_result(tokens, id, NULL);
			id = TD_WORD;
		}
		if (id == token->id && (id == TD_SINGLE_QUOTE
				|| id == TD_DOUBLE_QUOTE))
			id = TD_WORD;
		token_builder_free(token);
		token = token_builder_init(id);
	}
	else
		str_builder_add_char(token->builder, str[(*index)++]);
}

void	token_recognition(t_dlist **tokens, char *str)
{
	int				index;
	t_token_builder	*token;

	index = 0;
	token = token_builder_init(TD_WORD);
	while (str[index])
		token_recognition_handler(tokens, token, str, &index);
	add_token_to_result(tokens, token->id, token->builder->str);
	token_builder_free(token);
}
