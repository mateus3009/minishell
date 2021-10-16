/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:13 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/16 10:20:27 by msales-a         ###   ########.fr       */
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
	g_minishell.error_status = 0;
}

static void	go_to_oldpwd(char *arg)
{
	char	*oldpwd;

	oldpwd = find_env("OLDPWD");
	if (!oldpwd)
		error_handler("cd", "OLDPWD not set", 1);
	else
	{
		if (!ft_strcmp("-", arg))
			ft_putendl_fd(oldpwd, STDOUT_FILENO);
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

static void	go_home_tilde(void)
{
	char			*home;
	t_str_builder	*builder;

	home = find_env("HOME");
	if (home)
	{
		change_to_path(home);
		free(home);
		return ;
	}
	builder = str_builder_init();
	str_builder_add_str(builder, "/home/");
	str_builder_add_str(builder, getenv("USER"));
	change_to_path(builder->str);
	str_builder_destroy(builder);
}

void	cd_builtin(char **argv)
{
	if (argv[1] && argv[2])
		error_handler("cd", TOO_MANY_ARGS, 1);
	else if (!argv[1])
		go_home();
	else if (argv[1] && !ft_strcmp("~", argv[1]))
		go_home_tilde();
	else if (argv[1] && (!ft_strcmp("-", argv[1]) || !ft_strcmp("--", argv[1])))
		go_to_oldpwd(argv[1]);
	else if (argv[1] && *argv[1] == '-')
	{
		error_handler_arg("cd", argv[1], "invalid option", 2);
		ft_putstr_fd("cd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", STDERR_FILENO);
	}
	else if (argv[1])
		change_to_path(argv[1]);
}
