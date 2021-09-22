/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:19:35 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/21 20:47:40 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_variable(char *str, int *len)
{
	int	i;

	*len = 0;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i] || !str[i + 1] || (i && str[i - 1] == '\\')
		|| (!ft_isalnum(str[i + 1]) && str[i + 1] != '?'))
		return (NULL);
	*len = 1;
	if (str[i + 1] == '?' || ft_isdigit(str[i + 1]))
		return (str + i + 1);
	*len = 0;
	while (ft_isalnum((str + i + 1)[*len]))
		(*len)++;
	return (str + i + 1);
}

char	*expand_variable(char *str)
{
	int				len;
	char			*var;
	char			*key;
	char			*value;
	t_str_builder	*builder;

	var = find_variable(str, &len);
	if (!var)
		return (ft_strdup(str));
	key = ft_strndup(var, len);
	value = find_env(g_minishell.penv, key);
	if (!value)
		return ((free(key), ft_strdup("")));
	value = ft_strdup(value);
	builder = str_builder_init();
	str_builder_add_str_len(builder, str, var - str - 1);
	str_builder_add_str(builder, value);
	str_builder_add_str(builder, var + len);
	free(key);
	free(value);
	value = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (value);
}
