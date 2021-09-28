/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 21:17:10 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/27 20:53:58 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	RULES:
*	- without args -> $? = 0
*	- with args -> only one integer arg between
*	- check $? examples
	exit -1 => 255
	exit 23333 => 45
	exit asd => 2 =>
*/

void	exit_minishell(void)
{
	rl_clear_history();
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
