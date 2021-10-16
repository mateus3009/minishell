/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:05 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/16 11:04:25 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	comparator(const void *max, const void *min)
{
	const char	*foo;
	const char	*bar;

	foo = ((const char **)max)[0];
	bar = ((const char **)min)[0];
	return (ft_strcmp(foo, bar) > 0);
}

static void	show_environment(void)
{
	int		index;
	char	**env;
	char	**env_ordened;
	char	*value;

	index = -1;
	env = get_keys(g_minishell.env);
	env_ordened = heapsort(
			env, sizeof(char *), comparator, array_size((void **)env));
	while (env_ordened[++index])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_ordened[index], STDOUT_FILENO);
		value = find_hashmap_value(g_minishell.env, env_ordened[index]);
		if (value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			free(value);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

static void	error_variable(char *var)
{
	char	*line;

	g_minishell.error_status = 1;
	if (isatty(STDIN_FILENO))
	{
		ft_putstrs_fd(
			(char *[]){"minishell: export: `", var,
			"': not a valid identifier\n", NULL},
			STDERR_FILENO);
	}
	else
	{
		line = ft_itoa(g_minishell.general_line);
		ft_putstrs_fd(
			(char *[]){"minishell: line ", line, ": export: `", var,
			"': not a valid identifier\n", NULL},
			STDERR_FILENO);
		free(line);
	}
}

void	export_builtin(char	**args)
{
	size_t	index;

	if (!args[1])
	{
		show_environment();
		g_minishell.error_status = 0;
		return ;
	}
	index = 0;
	while (args[++index])
	{
		if (!ft_isalpha(*(args[index])) && *args[index] != '_')
		{
			error_variable(args[index]);
			g_minishell.error_status = 1;
			return ;
		}
		set_variable(args[index], g_minishell.env);
	}
	g_minishell.error_status = 0;
}
