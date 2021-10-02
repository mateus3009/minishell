/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:13 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/02 18:08:23 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_builtin(char **argv)
{
	char *home;
	char *oldpwd;

	if (argv[1] && argv[2])
	{
		error_handler(argv[0], TOO_MANY_ARGS, 1);
		return ;
	}
	//old = find_env(g_minishell.penv, "OLDPWD");
	if (!argv[1] || *argv[1] == '~')
	{
		home = find_env(g_minishell.penv, "HOME");
		if (!home)
			error_handler(argv[0], "HOME not set", 1);
		else if (chdir(home) == -1)
			error_handler(argv[0], strerror(errno), 1);
		// TODO set oldpwd e pwd env
		return ;
	}
	if (argv[1] && *argv[1] == '-')
	{
		oldpwd = find_env(g_minishell.penv, "OLDPWD");
		if (!oldpwd)
			error_handler(argv[0], "OLDPWD not set", 1);
		else if (chdir(oldpwd) == -1)
			error_handler(argv[0], strerror(errno), 1);
		// TODO set oldpwd e pwd env
		return ;
	}
	// TODO cd - (vai para o oldpwd)
	if (chdir(argv[1]) == -1)
	{
		error_handler(argv[0], strerror(errno), 1);
		return ;
	}
}
