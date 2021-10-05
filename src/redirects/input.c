/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:05:52 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/03 17:49:16 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_redirect(char *value)
{
	int	fd;

	fd = open(value, O_RDONLY);
	if (fd == -1)
	{
		error_handler(value, strerror(errno), 1);
		exit_minishell();
	}
	copy_buffer(fd, STDOUT_FILENO);
	close(fd);
}
