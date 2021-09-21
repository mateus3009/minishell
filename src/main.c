/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/20 21:03:53 by lniehues         ###   ########.fr       */
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
	while (1)
	{
		read_input_and_save_history(&line);
		if (!line)
			break ;
		tokens = NULL;
		token_recognition(&tokens, line);
		parse(tokens);
		free(line);
		ft_dlstclear(&tokens, token_free);
	}
	rl_clear_history();
	return (0);
}
