/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 21:44:05 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/28 21:01:47 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_command_length(t_dlist *current, t_dlist *end_or_pipe)
{
	int		i;
	t_token	*token;

	i = 0;
	while (current != end_or_pipe)
	{
		token = (t_token *)current->content;
		if (token->id == TD_WORD)
			i++;
		current = current->next;
	}
	return (i);
}

static char	**set_cmd_array_content(
	t_dlist *current, t_dlist *end_or_pipe, char **cmd_array)
{
	int		i;
	t_token	*token;

	i = 0;
	while (current != end_or_pipe)
	{
		token = (t_token *)current->content;
		if (token->id == TD_WORD || token->id == TD_DOUBLE_QUOTE)
			cmd_array[i++] = ft_strdup(token->value);
		current = current->next;
	}
	return (cmd_array);
}

char	**create_command(t_dlist *head, t_dlist *end_or_pipe)
{
	int		cmd_len;
	char	**cmd_array;

	cmd_len = get_command_length(head, end_or_pipe);
	cmd_array = malloc(sizeof(char *) * (cmd_len + 1));
	cmd_array[cmd_len] = NULL;
	cmd_array = set_cmd_array_content(head, end_or_pipe, cmd_array);
	return (cmd_array);
}
