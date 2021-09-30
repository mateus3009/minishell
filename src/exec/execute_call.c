/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:50:20 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 19:28:47 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		echo_builtin();
	if (ft_strcmp(argv[0], "cd") == 0)
		cd_builtin();
	if (ft_strcmp(argv[0], "pwd") == 0)
		pwd_builtin();
	if (ft_strcmp(argv[0], "export") == 0)
		export_builtin();
	if (ft_strcmp(argv[0], "unset") == 0)
		unset_builtin();
	if (ft_strcmp(argv[0], "env") == 0)
		env_builtin();
	if (ft_strcmp(argv[0], "exit") == 0)
		exit_builtin(argv);
}

void	execute_call(t_call	call)
{
	char	**argv;
	char	**env;

	argv = compile_argv(call.argv);
	execute_cmd_builtin(argv);
	if (!call.path)
		exit_minishell();
	env	= tpenv_to_array(g_minishell.penv);
	if (execve(call.path, argv, env) == -1)
		exit_minishell();
}
