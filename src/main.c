/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/26 16:06:43 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_dlist	*tokens;
	// struct stat coisa;

	// int result = stat("/home/msales-a/minishell", &coisa);
	// printf("%d %i %i %i\n", result, coisa.st_mode & __S_IFMT & __S_IFREG, coisa.st_mode & W_OK, coisa.st_mode & S_IXUSR);
	// return (0);
	g_minishell.error_status = 0;
	if (argc && argv)
		g_minishell.penv = parse_env(env);
	// char	*commands[2] = {"", NULL};
	// run_system_cmd(commands);
	// return (0);
	// char *path = find_env(g_minishell.penv, "PATH");
	// char *command = find_command_path(path, "echo");
	// printf("%s\n", command);
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
	return (0);
}

/*
int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		exitcode;
	char	**args;

	if (!argc && !argv)
		return (1);
	pid = fork();
	if (pid == -1)
		return (errno);
	else if (pid == 0)
	{
		args = (char*[4]){"echo", "teste", "uhu", NULL};
		if (execve("/bin/echofd", args, env) == -1)
			exit(errno);
	}
	else
	{
		waitpid(pid, &exitcode, 0);
		printf("pid: %d\nexit_code: %d\n", pid, exitcode);
	}
	return (0);
}
*/
