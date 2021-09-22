/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_handlers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:33:24 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/21 20:58:30 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_token(char *str, int *index)
{
	t_token_definition	*tokens;

	tokens = (t_token_definition[]){
	{.id = TD_HERE_FILE, .value = "<<", .length = 2},
	{.id = TD_AND, .value = "&&", .length = 2},
	{.id = TD_OR, .value = "||", .length = 2},
	{.id = TD_APPEND_MODE, .value = ">>", .length = 2},
	{.id = TD_PIPE, .value = "|", .length = 1},
	{.id = TD_INPUT, .value = ">", .length = 1},
	{.id = TD_OUTPUT, .value = "<", .length = 1},
	{.id = TD_DOUBLE_QUOTE, .value = "\"", .length = 1},
	{.id = TD_SINGLE_QUOTE, .value = "'", .length = 1},
	{.id = TD_SPACE, .value = " ", .length = 1},
	{.id = 0, .value = NULL}};
	while (tokens->value)
	{
		if (ft_strncmp(tokens->value, str + *index, tokens->length) == 0)
		{
			*index += tokens->length;
			return (tokens->id);
		}
		tokens++;
	}
	return (0);
}

int	find_end_quote_token(char *str, int *index, t_token_builder *token)
{
	char	id;

	if (token->id == TD_SINGLE_QUOTE)
		id = '\'';
	if (token->id == TD_DOUBLE_QUOTE)
		id = '\"';
	if (str[*index] == id)
	{
		(*index)++;
		return (token->id);
	}
	return (0);
}

int	find_end_of_token(
	char *str,
	int *index,
	t_token_builder *token)
{
	int	id;

	if (token->id == TD_SINGLE_QUOTE || token->id == TD_DOUBLE_QUOTE)
		return (find_end_quote_token(str, index, token));
	id = find_token(str, index);
	while (id == TD_SPACE && str[*index] == ' ')
		(*index)++;
	return (id);
}

void	add_token_to_result(
	t_dlist **tokens,
	int id,
	char *str)
{
	t_token	*token;
	t_dlist	*node;

	if (id == TD_WORD && (!str || !ft_strlen(str)))
		return ;
	token = token_init(id, str);
	node = ft_dlstnew(token);
	if (!token || !node)
		exit(EXIT_FAILURE);
	ft_dlstadd_back(tokens, node);
}
