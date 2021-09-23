/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/22 21:43:56 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_dlist	*tokens;


	g_minishell.error_status = 0;
	if (argc && argv)
		g_minishell.penv = parse_env(env);
	char **coisas = tpenv_to_array(g_minishell.penv);
	while (*coisas) {
		printf("-> %s\n", *coisas);
		coisas++;
	}
	while (1)
	{
		tokens = NULL;
		read_input_and_save_history(&line);
		token_recognition(&tokens, line);
		parse(tokens);
		free(line);
		ft_dlstclear(&tokens, token_free);
	}
	rl_clear_history();
	return (0);
}
