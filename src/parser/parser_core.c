/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/06 23:41:11 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef	bool (* t_token_parser)(t_dlist **new, t_dlist **tokens);

void	core(t_dlist **tokens, t_token_parser *parsers)
{
	t_dlist	*new;
	t_dlist *token;
	t_token	*temp;
	int		index;

	new = NULL;
	token = *tokens;
	while (token)
	{
		index = -1;
		while (parsers[++index])
		{
			if (parsers[index](&new, &token))
				break ;
		}
		if (!parsers[index])
		{
			temp = token->content;
			ft_dlstadd_back(new,
				ft_dlstnew(token_init(temp->id, temp->value)));
		}
	}
	ft_dlstclear(tokens, token_free);
	*tokens = new;
}

void	parse(t_dlist **ptr_tokens)
{
	t_token_parser	*parsers;

	parsers = (t_token_parser[]){NULL};
	core(ptr_tokens, parsers);
	exit(0);
}
