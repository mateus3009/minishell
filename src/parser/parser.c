/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/05 20:41:49 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef	bool (* t_token_parser)(t_dlist **new, t_dlist **tokens);

void	core(t_dlist **tokens, t_token_parser *parser)
{
	t_dlist	*new;
	t_dlist *token;
	int		index;

	new = NULL;
	token = *tokens;
	while (token)
	{
		index = -1;
		while (parser[++index])
		{
			if (parser[index](&new, &token))
				break ;
		}
	}
	ft_dlstclear(tokens, token_free);
	*tokens = new;
}

bool	set_parser(t_dlist **new, t_dlist **tokens)
{
	t_token			*token;

	token = (*tokens)->content;
	if (token->id != TD_WORD || !ft_isalpha(*token->value)
		|| !ft_strchr(token->value, '='))
		return (false);
	if ((*tokens)->previous
			&& (((t_token *)(*tokens)->previous->content)->id != TD_SPACE))
		return (false);
	// TODO
	return (false);
}

bool	here_document_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;

	token = (*tokens)->content;
	if (token->id != TD_HERE_DOCUMENT)
		return (false);
	if ((*tokens)->next)
	{
		token = (*tokens)->next;
		if (token->id == TD_SPACE)
			token = (*tokens)->next;
		if (!token || token->id != TD_WORD )
			return (false);
	}
	return (false);
}

bool	variables_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;

	token = (*tokens)->content;
	if (!new)
		return (false);

	return (false);
}

bool	redirects_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;

	token = (*tokens)->content;
	if (token->id != TD_INPUT && token->id != TD_OUTPUT
		&& token->id != TD_APPEND_MODE)
		return (false);
	ft_dlstadd_back(new, ft_dlstnew(token_init(token->id, token->value)));
	*tokens = (*tokens)->next;
	return (false);
}

bool	operators_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;

	token = (*tokens)->content;
	if (token->id != TD_PIPE && token->id != TD_AND && token->id != TD_OR)
		return (false);
	ft_dlstadd_back(new, ft_dlstnew(token_init(token->id, token->value)));
	*tokens = (*tokens)->next;
	return (true);
}

bool	word_parser(t_dlist **new, t_dlist **tokens)
{
	t_token			*token;
	t_str_builder	*builder;

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
		ft_dlstadd_back(new, ft_dlstnew(token_init(TD_WORD, builder->str)));
		str_builder_destroy(builder);
		return (true);
	}
	return (false);
}

bool	space_parser(t_dlist **new, t_dlist **tokens)
{
	t_token	*token;

	token = (*tokens)->content;
	if (token->id != TD_SPACE)
		return (false);
	*tokens = (*tokens)->next;
	return (true);
}

void	parse(t_dlist **ptr_tokens)
{
	parse_expand_all_variables(ptr_tokens);
	join_word(ptr_tokens);
	parse_here_document(ptr_tokens);
}
