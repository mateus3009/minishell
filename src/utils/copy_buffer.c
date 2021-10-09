/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:43:20 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/03 17:43:32 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUFFER_SIZE 100

void	copy_buffer(int from_fd, int to_fd)
{
	int	buffer[BUFFER_SIZE];
	int	readed;

	readed = 1;
	while (readed)
	{
		readed = read(from_fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			perror(strerror(errno));
			exit_minishell();
		}
		if (write(to_fd, buffer, readed) == -1)
		{
			perror(strerror(errno));
			exit_minishell();
		}
	}
}
