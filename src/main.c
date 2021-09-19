/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/19 18:40:12 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	t_dlist *tokens;
	t_token *token;

	g_minishell.error_status = 0;
	if (argc && argv)
		g_minishell.penv = parse_env(env);
	while (1)
	{
		read_input(&line);
		if (!line)
			break ;
		tokens = NULL;
		token_recognition(&tokens, line);
		while (tokens)
		{
			token = (t_token *)tokens->content;
			if (token->id == TD_WORD || token->id == TD_DOUBLE_QUOTE)
			{
				char *new = expand_variable(token->value);
				free(token->value);
				token->value = new;
			}
			printf("<%d, %s>\n", token->id, token->value);

			tokens = tokens->next;
		}
		free(line);
		ft_dlstclear(&tokens, token_free);
	}
	rl_clear_history();
	return (0);
}
