/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:44:05 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/25 19:13:32 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_command_length(t_dlist *current)
{
	int		i;
	t_token	*token;

	i = 0;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->id == TD_WORD)
			i++;
		current = current->next;
	}
	return (i);
}

static char	**set_cmd_array_content(t_dlist *tokens, char **cmd_array)
{
	int		i;
	t_token	*token;

	i = 0;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->id == TD_WORD || token->id == TD_DOUBLE_QUOTE)
			cmd_array[i++] = ft_strdup(token->value);
		tokens = tokens->next;
	}
	return (cmd_array);
}

char	**create_command(t_dlist *tokens)
{
	int		cmd_len;
	char	**cmd_array;

	cmd_len = get_command_length(tokens);
	cmd_array = malloc(sizeof(char *) * (cmd_len + 1));
	cmd_array[cmd_len] = NULL;
	cmd_array = set_cmd_array_content(tokens, cmd_array);
	return (cmd_array);
}
