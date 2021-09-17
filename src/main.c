/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/16 22:05:13 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *const argv[], char *const env[])
{
    char    *line;
	//t_penv	*penv;

	// if (argc && argv)
	// {
	// 	penv = parse_env(env);
	// 	display_env(penv);
	// 	printf("\n\n");
	// 	printf("->PATH: %s\n", find_env(penv, "PATH"));
	// 	free_env(penv);
	// 	execve("/usr/bin/echo", argv, env);
	// }

	line = NULL;
    while (true && argc)
    {
        line = readline(NULL);
        if (!line)
            break ;
		printf("O que você escreveu: %s\n", line);
		run_system_cmd(line, argv, env);
		add_history(line);
		free(line);
    }
	rl_clear_history();
    return (0);
}
