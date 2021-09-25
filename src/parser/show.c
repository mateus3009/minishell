/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:43:42 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/25 17:35:20 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_tokens(t_dlist **ptr_tokens)
{
	t_dlist				*tokens;
	t_token				*token;
	t_token_definition	*def;
	int					index;

	def = (t_token_definition[]){
	{.id = TD_HERE_DOCUMENT, .value = "<<"}, {.id = TD_AND, .value = "&&"},
	{.id = TD_OR, .value = "||"}, {.id = TD_APPEND_MODE, .value = ">>"},
	{.id = TD_PIPE, .value = "|"}, {.id = TD_INPUT, .value = ">"},
	{.id = TD_OUTPUT, .value = "<"}, {.id = TD_DOUBLE_QUOTE, .value = "\""},
	{.id = TD_SINGLE_QUOTE, .value = "'"}, {.id = TD_SPACE, .value = " "},
	{.id = 0, .value = NULL}};
	tokens = *ptr_tokens;
	while (tokens)
	{
		index = 0;
		token = (t_token *)tokens->content;
		while (token->id && def[index].id && token->id != def[index].id)
			index++;
		printf("<%d, ", token->id);
		if (token->id != TD_WORD)
			printf("%s>\n", def[index].value);
		else
			printf("%s>\n", token->value);
		tokens = tokens->next;
	}
}
