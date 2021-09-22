/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 21:17:10 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/21 21:39:10 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(void)
{
	free_env(g_minishell.penv);
	exit(g_minishell.error_status);
}

/*
void	exit_builtin(char **argv)
{
	int argc;
	argc = get_argc(argv);
	if (argc > 1)
	{
		prompt_error_msg(cmd, msg, fd);
		return ;
	}
	ft_putstr_fd("exit\n", 1);
	exit_minishell();
}
*/
