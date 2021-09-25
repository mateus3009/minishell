/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:46:07 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/25 16:22:56 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_document(char *value)
{
	t_str_builder	*builder;
	char			*line;

	builder = str_builder_init();
	while (true)
	{
		line = readline("> ");
		if (!line)
			return ((str_builder_destroy(builder), NULL));
		if (ft_strcmp(value, line) == 0)
			break ;
		str_builder_add_str(builder, line);
		free(line);
	}
	line = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (line);
}

t_dlist	*next_word(t_dlist *tokens)
{
	t_token	*token;

	token = NULL;
	tokens = tokens->next;
	if (tokens)
		token = tokens->content;
	if (token && token->id == TD_SPACE)
		tokens = tokens->next;
	if (tokens)
		token = tokens->content;
	if (token && token->id == TD_WORD)
		return (tokens);
	return (NULL);
}

t_dlist	*previous_number(t_dlist *tokens, int *number)
{
	t_token	*token;
	char	*endptr;
	int		result;

	token = NULL;
	tokens = tokens->previous;
	if (tokens)
		token = tokens->content;
	if (token && token->id == TD_WORD)
	{
		result = ft_strtol(token->value, &endptr, 10);
		if (!*endptr)
		{
			*number = result;
			return (tokens);
		}
	}
	return (NULL);
}

void	ft_dlstdel(t_dlist **list, t_dlist *node, void (*del)(void*))
{
	t_dlist	*previous;
	t_dlist	*next;

	if (!list || !*list || !node)
		return ;
	previous = node->previous;
	next = node->next;
	ft_dlstdelone(node, del);
	if (previous)
		previous->next = next;
	if (next)
		next->previous = previous;
	if (*list == node)
		*list = NULL;
}

int	parse_previous_number(t_dlist **ptr_tokens, int normal)
{
	int		number;
	t_dlist	*fd;

	number = normal;
	fd = previous_number(*ptr_tokens, &number);
	ft_dlstdel(ptr_tokens, fd, token_free);
	return (number);
}

char	*parse_next_word(t_dlist **ptr_tokens)
{
	char	*result;
	t_dlist	*word;
	t_token	*token;

	result = NULL;
	word = next_word(*ptr_tokens);
	if (word)
	{
		token = word->content;
		result = ft_strdup(token->value);
	}
	ft_dlstdel(ptr_tokens, word, token_free);
	return (result);
}

void	parse_here_document_node(t_dlist **ptr_tokens)
{
	int		number;
	char	*word;
	t_token	*token;

	if (!ptr_tokens || !*ptr_tokens)
		return ;
	token = (*ptr_tokens)->content;
	if (token->id != TD_HERE_DOCUMENT)
		return ;
	number = parse_previous_number(ptr_tokens, STDIN_FILENO);
	word = parse_next_word(ptr_tokens);
	if (!word)
		exit(2);
	token->value = here_document(word);
	free(word);
	word = token->value;
	token->value = expand_all_variables(word);
	free(word);
}

void	parse_here_document(t_dlist **ptr_tokens)
{
	t_dlist	*tokens;

	tokens = *ptr_tokens;
	while (tokens)
	{
		parse_here_document_node(&tokens);
		tokens = tokens->next;
	}
}
