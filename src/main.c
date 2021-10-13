/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/12 19:28:29 by msales-a         ###   ########.fr       */
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
	open_std_fd();
	while (1)
	{
		tokens = NULL;
		read_input_and_save_history(&line);
		tokens = token_recognition(line);
		tokens_validator(tokens);
		here_document_parser(&tokens);
		process_commands(tokens);
		ft_dlstclear(&tokens, token_free);
		free(line);
	}
	rl_clear_history();
	free_hashmap_bucket(g_minishell.local_var);
	free_hashmap_bucket(g_minishell.env);
	close_std_fd();
	return (0);
}
