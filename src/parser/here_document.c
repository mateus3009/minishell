/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:46:07 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 20:36:54 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_document(char *value)
{
	t_str_builder	*builder;
	char			*line;

	builder = str_builder_init();
	while (true)
	{
		line = readline("> ");
		if (!line)
			return ((str_builder_destroy(builder), NULL));
		if (ft_strcmp(value, line) == 0)
			break ;
		str_builder_add_str(builder, line);
		str_builder_add_char(builder, '\n');
		free(line);
	}
	line = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (line);
}
