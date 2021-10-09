/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/09 10:39:34 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_lists(t_dlist **old, t_dlist **new)
{
	ft_dlstclear(new, token_free);
	*new = NULL;
	ft_dlstclear(old, token_free);
	*old = NULL;
}

void	parser_core(t_dlist **tokens, t_token_parser *parsers)
{
	t_dlist	*new;
	t_dlist	*token;
	int		index;
	int		result;

	new = NULL;
	token = *tokens;
	while (token)
	{
		index = -1;
		while (parsers[++index])
		{
			result = parsers[index](&new, &token);
			if (result != 0)
				break ;
		}
		if (!parsers[index] || result == -1)
		{
			clear_lists(tokens, &new);
			return ;
		}
	}
	ft_dlstclear(tokens, token_free);
	*tokens = new;
}
