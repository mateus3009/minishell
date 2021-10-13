/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:02 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/13 13:01:21 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_alnum(char *value)
{
	if (!value || !*value)
		return (false);
	while (*value)
	{
		if (!ft_isalnum(*value))
			return (false);
		value++;
	}
	return (true);
}

static void	error_variable(char *var)
{
	g_minishell.error_status = 1;
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

void	unset_builtin(char **args)
{
	size_t	index;

	if (!args[1])
		return ;
	index = 0;
	while (args[++index])
	{
		if (!is_alnum(args[index]))
		{
			error_variable(args[index]);
			return ;
		}
		remove_from_hashmap(g_minishell.env, args[index]);
	}
	g_minishell.error_status = 0;
}
