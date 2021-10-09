/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/09 11:54:19 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_dlist	*tokens;

	if (argc && argv)
		g_minishell.penv = parse_env(env);
	open_std_fd();
	while (1)
	{
		tokens = NULL;
		read_input_and_save_history(&line);
		tokens = token_recognition(line);
		tokens_validator(tokens);
		here_document_parser(&tokens);
		if (tokens)
			show_tokens(&tokens);
		//parse(&tokens);
		//create_and_run_pipeline(tokens);
		ft_dlstclear(&tokens, token_free);
		free(line);
	}
	rl_clear_history();
	free_env(g_minishell.penv);
	close_std_fd();
	return (0);
}
