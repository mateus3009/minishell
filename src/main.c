/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/17 11:21:28 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_dlist	*tokens;

	if (argc > 1 && argv)
		error_handler("minishell", TOO_MANY_ARGS, 4242);
	g_minishell.local_var = create_hashmap_bucket(100);
	g_minishell.env = env_to_hashmap(env);
	g_minishell.interactive = isatty(STDIN_FILENO);
	open_std_fd();
	ignore_signals();
	while (1)
	{
		tokens = NULL;
		read_input_and_save_history(&line);
		if (!line)
			continue;
		tokens = token_recognition(line);
		if(!tokens_validator(tokens) && !g_minishell.interactive)
		{
			error_simple(line, 2);
			break ;
		}
		here_document_parser(&tokens);
		process_commands(tokens);
		ft_dlstclear(&tokens, token_free);
		free(line);
	}
	rl_clear_history();
	free_hashmap_bucket(g_minishell.local_var);
	free_hashmap_bucket(g_minishell.env);
	close_std_fd();
	return (g_minishell.error_status);
}
