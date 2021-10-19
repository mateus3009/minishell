/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_formater.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 08:53:05 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/19 09:07:00 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_and_organize_path(char *path)
{
	size_t	index;
	size_t	position;
	char	**folders;
	char	**parts;

	index = -1;
	position = 0;
	parts = ft_split(path, '/');
	folders = ft_calloc(ft_count_segment(path, '/') + 1, sizeof(char *));
	while (parts[++index])
	{
		if (!ft_strcmp("..", parts[index]) || !ft_strcmp(".", parts[index]))
		{
			if (!ft_strcmp(".", parts[index]) || !position)
				continue ;
			position--;
			free(folders[position]);
			folders[position] = NULL;
			continue ;
		}
		folders[position] = ft_strdup(parts[index]);
		position++;
	}
	free_str_array(parts);
	return (folders);
}

static char	*format_path(char *path)
{
	int				index;
	char			**folders;
	t_str_builder	*builder;

	index = -1;
	folders = split_and_organize_path(path);
	builder = str_builder_init();
	str_builder_add_char(builder, '/');
	while (folders[++index])
	{
		str_builder_add_str(builder, folders[index]);
		if (folders[index + 1])
			str_builder_add_char(builder, '/');
	}
	path = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (path);
}

static char	*remove_slash_path(char *path)
{
	t_str_builder	*builder;
	int				index;

	if (!path)
		return (NULL);
	index = 0;
	builder = str_builder_init();
	while (path[index])
	{
		if (path[index] != '/' || (path[index] == '/' && path[index + 1]))
			str_builder_add_char(builder, path[index]);
		while (path[index] == '/' && path[index + 1] == '/')
			index++;
		index++;
	}
	path = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (path);
}

char	*join_path(char *a, char *b)
{
	t_str_builder	*builder;

	builder = str_builder_init();
	if (*b != '/')
	{
		str_builder_add_str(builder, a);
		str_builder_add_char(builder, '/');
	}
	str_builder_add_str(builder, b);
	a = remove_slash_path(builder->str);
	b = format_path(a);
	free(a);
	str_builder_destroy(builder);
	return (b);
}
