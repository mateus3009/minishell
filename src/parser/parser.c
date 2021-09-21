/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/20 21:03:02 by lniehues         ###   ########.fr       */
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
