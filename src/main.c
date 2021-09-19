/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/19 14:19:17 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*backslash_newline_handler(char *str)
{
	return (ft_strreplace_all2(str, "\\\n", ""));
}

typedef struct s_token_definition
{
	short	id;
	char	*value;
	size_t	length;
}				t_token_definition;

typedef struct s_token_builder
{
	short			id;
	t_str_builder	*builder;
}				t_token_builder;

void	backslash_handler(
	char *str,
	int *index,
	t_token_builder *token)
{
	while (str[*index] == '\\')
	{
		if (!str[*index + 1])
			return ;
		str_builder_add_str_len(token->builder, str + *index, 2);
		index += 2;
	}
}

typedef struct s_token
{
	short	id;
	char	*value;
}				t_token;

#define TD_WORD			0
#define TD_HERE_FILE	1
#define TD_AND			2
#define TD_OR			3
#define TD_APPEND_MODE	4
#define TD_EXIT_STATUS	5
#define TD_SPACE		6
#define TD_SINGLE_QUOTE	7
#define TD_DOUBLE_QUOTE	8
#define TD_PIPE			9
#define TD_INPUT		10
#define TD_OUTPUT		11
#define TD_VARIABLE		12

int	find_token(char *str, int *index)
{
	t_token_definition	*tokens;

	tokens = (t_token_definition[]){
	{.id = TD_HERE_FILE, .value = "<<", .length = 2},
	{.id = TD_AND, .value = "&&", .length = 2},
	{.id = TD_OR, .value = "||", .length = 2},
	{.id = TD_APPEND_MODE, .value = ">>", .length = 2},
	{.id = TD_EXIT_STATUS, .value = "$?", .length = 2},
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

int	find_the_end_of_current_token_or_new_token(
	char *str,
	int	*index,
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

t_token_builder	*token_builder_init(int id)
{
	t_token_builder	*token;

	token = malloc(sizeof(token));
	if (!token)
		return (NULL);
	token->id = id;
	token->builder = str_builder_init();
	return (token);
}

void	token_builder_free(t_token_builder *token_builder)
{
	str_builder_destroy(token_builder->builder);
	free(token_builder);
}

t_token	*token_init_raw(int id, char *str)
{
	t_token	*token;

	token = malloc(sizeof(token));
	if (!token)
		return (NULL);
	token->id = id;
	token->value = str;
	return (token);
}

t_token	*token_init(t_token_builder *token_builder)
{
	char	*str;

	str = ft_strdup(token_builder->builder->str);
	if (!str)
		return (NULL);
	return (token_init_raw(token_builder->id, str));
}

void	token_free(t_token *token)
{
	free(token->value);
	free(token);
}

void	add_the_curent_token_to_the_result(
	t_dlist **tokens,
	t_token_builder *builder)
{
	t_token	*token;
	t_dlist	*node;

	if (builder->id == TD_WORD && !builder->builder->used)
		return ;
	token = token_init(builder);
	node = ft_dlstnew(token);
	if (!token || !node)
		exit(EXIT_FAILURE);
	ft_dlstadd_back(tokens, node);
}

void	add_the_curent_token_id_to_the_result(t_dlist **tokens, int id)
{
	t_token	*token;
	t_dlist	*node;

	token = token_init_raw(id, NULL);
	node = ft_dlstnew(token);
	if (!token || !node)
		exit(EXIT_FAILURE);
	ft_dlstadd_back(tokens, node);
}

void	token_recognition(t_dlist **tokens, char *str)
{
	int				index;
	t_token_builder	*token;
	int				id;

	index = 0;
	token = token_builder_init(TD_WORD);
	while (str[index])
	{
		backslash_handler(str, &index, token);
		id = find_the_end_of_current_token_or_new_token(str, &index, token);
		if (id)
		{
			add_the_curent_token_to_the_result(tokens, token);
			if (id != token->id && id != TD_SINGLE_QUOTE && id != TD_DOUBLE_QUOTE)
			{
				add_the_curent_token_id_to_the_result(tokens, id);
				id = TD_WORD;
			}
			if (id == token->id && (id == TD_SINGLE_QUOTE || id == TD_DOUBLE_QUOTE))
				id = TD_WORD;
			token_builder_free(token);
			token = token_builder_init(id);
		}
		else
			str_builder_add_char(token->builder, str[index++]);
	}
	add_the_curent_token_to_the_result(tokens, token);
	token_builder_free(token);
}

int	main(void)
{
	char	*line;
	t_dlist	*tokens;
	t_token	*token;

	tokens = NULL;
	line = "echo \'a\'b c";
	line = backslash_newline_handler(line);
	token_recognition(&tokens, line);
	while (tokens)
	{
		token = (t_token *)tokens->content;
		printf("type: %d\nvalue:%s\n\n", token->id, token->value);
		tokens = tokens->next;
	}
	return (0);
}
