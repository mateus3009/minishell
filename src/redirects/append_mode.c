/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:04:22 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/03 17:48:00 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_mode_redirect(char *value)
{
	int	fd;

	fd = open(value, O_CREAT | O_APPEND | O_WRONLY, 644);
	if (fd == -1)
	{
		error_handler(value, strerror(errno), 1);
		exit_minishell();
	}
	copy_buffer(STDIN_FILENO, fd);
	close(fd);
}
