/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:18 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:23:58 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(char **argv)
{
	size_t	index;
	bool	new_line;

	index = 1;
	new_line = true;
	if (argv[1] && ft_strcmp("-n", argv[1]) == 0)
	{
		new_line = false;
		index++;
	}
	while (argv[index])
	{
		ft_putstr_fd(argv[index], STDOUT_FILENO);
		if (argv[++index])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	g_minishell.error_status = 0;
}
