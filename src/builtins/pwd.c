/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:09 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/13 15:29:06 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(void)
{
	char	path[4096];

	if (!getcwd(path, 4096))
	{
		error_handler("pwd", strerror(errno), 1);
		exit_minishell();
	}
	ft_putendl_fd(path, STDOUT_FILENO);
}
