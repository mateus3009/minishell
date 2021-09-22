/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/21 21:27:25 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_dlist *tokens)
{
	t_token	*token;
	char	*new;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->id == TD_WORD || token->id == TD_DOUBLE_QUOTE)
		{
			new = expand_variable(token->value);
			free(token->value);
			token->value = new;
		}
		printf("<%d, %s>\n", token->id, token->value);
		tokens = tokens->next;
	}
}
