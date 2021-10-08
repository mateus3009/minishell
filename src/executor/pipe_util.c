/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 07:43:57 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/02 13:54:58 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(int	**fd)
{
	if (!fd)
		return ;
	*fd = malloc(sizeof(int) * 2);
	if (!fd)
		exit_minishell();
	if (pipe(*fd) == -1)
		exit_minishell();
}

void	free_pipe(int *fd)
{
	if (!fd)
		return ;
	close(fd[0]);
	close(fd[1]);
	free(fd);
}

void	configure_reader_pipe(int *fd)
{
	if (!fd)
		return ;
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit_minishell();
}

void	configure_writer_pipe(int *fd)
{
	if (!fd)
		return ;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit_minishell();
}
