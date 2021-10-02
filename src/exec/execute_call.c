/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:50:20 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/02 16:19:56 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	execute_cmd_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return ((echo_builtin(argv), true));
	if (ft_strcmp(argv[0], "cd") == 0)
		return ((cd_builtin(), true));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return ((pwd_builtin(), true));
	if (ft_strcmp(argv[0], "export") == 0)
		return ((export_builtin(), true));
	if (ft_strcmp(argv[0], "unset") == 0)
		return ((unset_builtin(), true));
	if (ft_strcmp(argv[0], "env") == 0)
		return ((env_builtin(), true));
	if (ft_strcmp(argv[0], "exit") == 0)
		return ((exit_builtin(argv), true));
	return (false);
}

void	execute_call(t_call	call)
{
	char	**argv;
	char	**env;

	argv = str_list_array(call.argv);
	env	= tpenv_to_array(g_minishell.penv);
	if (!execute_cmd_builtin(argv))
	{
		if (!call.path)
			exit_minishell();
		if (execve(call.path, argv, env) == -1)
			exit_minishell();
	}
	free_str_array(argv);
	free_str_array(env);
}
