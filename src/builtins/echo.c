/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:19:18 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/02 16:23:27 by msales-a         ###   ########.fr       */
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
		printf("%s", argv[index]);
		if (argv[++index])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}
