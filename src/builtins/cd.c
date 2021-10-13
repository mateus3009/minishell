/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:13 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/13 14:02:50 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_to_path(char *path)
{
	char	*current_dir;
	char	*err_msg;
	char	buffer[2048];

	current_dir = getcwd(buffer, 2048);
	insert_on_hashmap("OLDPWD", current_dir, g_minishell.env);
	if (chdir(path) != 0 && ft_strchr(path, '>') == NULL)
	{
		err_msg = ft_strjoin("cd: ", path);
		error_handler(err_msg, strerror(errno), 1);
		free(err_msg);
		return ;
	}
	current_dir = getcwd(buffer, 2048);
	insert_on_hashmap("PWD", current_dir, g_minishell.env);
}

static void	go_to_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = find_env("OLDPWD");
	if (!oldpwd)
		error_handler("cd", "OLDPWD not set", 1);
	else
	{
		printf("%s\n", oldpwd);
		change_to_path(oldpwd);
	}
	free(oldpwd);
}

static void	go_home(void)
{
	char	*home;

	home = find_env("HOME");
	if (!home)
		error_handler("cd", "HOME not set", 1);
	else
		change_to_path(home);
	free(home);
}

void	cd_builtin(char **argv)
{
	char	*current_dir;

	if (argv[1] && argv[2])
		error_handler("cd", TOO_MANY_ARGS, 1);
	else if (!argv[1] || *argv[1] == '~')
		go_home();
	else if (argv[1] && *argv[1] == '-')
		go_to_oldpwd();
	else
	{
		current_dir = ft_strdup(argv[1]);
		change_to_path(current_dir);
		free(current_dir);
	}
}
