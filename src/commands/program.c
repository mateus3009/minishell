/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 19:32:52 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/13 12:52:35 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	execute_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return ((echo_builtin(argv), true));
	if (ft_strcmp(argv[0], "cd") == 0)
		return ((cd_builtin(argv), true));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return ((pwd_builtin(), true));
	if (ft_strcmp(argv[0], "export") == 0)
		return ((export_builtin(argv), true));
	if (ft_strcmp(argv[0], "unset") == 0)
		return ((unset_builtin(argv), true));
	if (ft_strcmp(argv[0], "env") == 0)
		return ((env_builtin(), true));
	if (ft_strcmp(argv[0], "exit") == 0)
		return ((exit_builtin(argv), true));
	return (false);
}

void	execute_external(char **argv)
{
	char	**env;
	char	*path;

	env = hashmap_env_to_array_env(g_minishell.env);
	path = find_command_path(
		find_env("PATH"), argv[0]);
	if (execve(path, argv, env) == -1)
	{
		if (!path)
			error_handler(argv[0], "command not found", 127);
		else
			error_handler(argv[0], strerror(errno), errno);
		free_str_array(env);
		free(path);
		exit(127);
	}
}

pid_t	execute_program(t_command *command)
{
	pid_t	pid;
	char	**argv;

	pid = 0;
	argv = str_list_array(command->words);
	if (execute_builtin(argv))
		return ((free_str_array(argv), pid));
	if (command->op != TD_PIPE)
		pid = fork();
	if (pid == -1)
		exit_minishell();
	set_exec_signals();
	if (pid == 0)
	{
		execute_external(argv);
	}
	free_str_array(argv);
	return (pid);
}
