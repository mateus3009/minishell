/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:02 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/15 20:37:38 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_alnum(char *value)
{
	if (!value || !*value || (!ft_isalpha(*value) && *value != '_'))
		return (false);
	while (*value)
	{
		if (!ft_isalnum(*value) && *value != '_')
			return (false);
		value++;
	}
	return (true);
}

static void	error_variable(char *var)
{
	g_minishell.error_status = 1;
	ft_putstrs_fd(
		(char *[]){"minishell: unset: `", var, "': not a valid identifier"},
		STDERR_FILENO);
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
