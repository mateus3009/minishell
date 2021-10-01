/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 21:39:34 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 21:50:46 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_std_fd(void)
{
	g_minishell.fd_in = dup(STDIN_FILENO);
	g_minishell.fd_out = dup(STDOUT_FILENO);
}

void	restore_std_fd(void)
{
	dup2(g_minishell.fd_in, STDIN_FILENO);
	close(g_minishell.fd_in);
	dup2(g_minishell.fd_out, STDOUT_FILENO);
	close(g_minishell.fd_out);
}
