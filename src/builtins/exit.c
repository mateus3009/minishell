/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 21:17:10 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/30 19:39:38 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	EXPECTED BEHAVIOR:
*
*	- no args -> exits -> $? == {last_exit_status}
*	- one num arg -> exits -> $? == {arg_num}
*	- more than one arg -> doesn't exits -> $? == 1
*	- one or more non-num args -> exits -> $? == 2
*/

void	error_handler(char *cmd, char *err_msg, int err_number)
{
	t_str_builder	*builder;
	char			*prompt_error;

	builder = str_builder_init();
	str_builder_add_str(builder, "minishell : ");
	str_builder_add_str(builder, cmd);
	str_builder_add_str(builder, " : ");
	str_builder_add_str(builder, err_msg);
	prompt_error = ft_strdup(builder->str);
	str_builder_destroy(builder);
	ft_putendl_fd(prompt_error, 2);
	free(prompt_error);
	g_minishell.error_status = err_number;
}

void	exit_minishell(void)
{
	rl_clear_history();
	free_env(g_minishell.penv);
	exit(g_minishell.error_status);
}

static int	get_argc(char **argv)
{
	int	i;

	i = 0;
	while (*(++argv))
		i++;
	return (i);
}

static bool	arg_only_digit(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit((int)arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	validate_first_arg(char *arg)
{
	if (!arg)
		return ;
	if (arg_only_digit(arg))
	{
		g_minishell.error_status = ft_atoi(arg);
		return ;
	}
	error_handler("exit", NUM_ARG_REQUIRED, 2);
	exit_minishell();
}

void	exit_builtin(char **argv)
{
	int	argc;

	ft_putstr_fd("exit\n", 1);
	argc = get_argc(argv);
	validate_first_arg(argv[1]);
	if (argc > 1)
	{
		error_handler("exit", TOO_MANY_ARGS, 1);
		return ;
	}
	exit_minishell(); // TODO o exit está matando o processo filho e não o minishell
}
