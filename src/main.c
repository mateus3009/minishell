/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/27 21:45:13 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_dlist	*tokens;

	if (argc && argv)
		g_minishell.penv = parse_env(env);
	while (1)
	{
		tokens = NULL;
		read_input_and_save_history(&line);
		token_recognition(&tokens, line);
		parse(&tokens);
		ft_dlstclear(&tokens, token_free);
		free(line);
	}
	rl_clear_history();
	free_env(g_minishell.penv);
	return (0);
}
