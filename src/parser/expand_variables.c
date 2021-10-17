/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:19:35 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/17 13:59:19 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_variable(char *str, int *len)
{
	int	i;

	*len = 0;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i] || !str[i + 1] || (i && str[i - 1] == '\\')
		|| (!ft_isalnum(str[i + 1]) && str[i + 1] != '?' && str[i + 1] != '_'))
		return (NULL);
	*len = 1;
	if (str[i + 1] == '?' || ft_isdigit(str[i + 1]))
		return (str + i + 1);
	*len = 0;
	while (ft_isalnum((str + i + 1)[*len]) || (str + i + 1)[*len] == '_')
		(*len)++;
	return (str + i + 1);
}

char	*expand_variabledasdsa(char *str)
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
	value = find_hashmap_value(g_minishell.local_var, key);
	if (!value)
		value = find_env(key);
	free(key);
	builder = str_builder_init();
	str_builder_add_str_len(builder, str, var - str - 1);
	str_builder_add_str(builder, value);
	str_builder_add_str(builder, var + len);
	free(value);
	value = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (value);
}

char	*expand_all_variables_(char *str)
{
	int				len;
	t_str_builder	*builder;
	char			*temp;
	char			*key;

	if (!str)
		return (NULL);
	builder = str_builder_init();
	while (true)
	{
		temp = find_variable(str, &len);
		if (!temp)
		{
			str_builder_add_str(builder, str);
			break ;
		}
		str_builder_add_str_len(builder, str, temp - str - 1);
		key = ft_strndup(temp, len);
		str = temp + len;
		temp = find_hashmap_value(g_minishell.local_var, key);
		if (!temp)
			temp = find_hashmap_value(g_minishell.env, key);
		str_builder_add_str(builder, temp);
		free(temp);
		free(key);
	}
	temp = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (temp);
}

static void	expand_and_add_to_builder(t_str_builder **builder, t_token *token)
{
	char	*temp;

	if (!builder || !*builder)
		*builder = str_builder_init();
	if (token->id == TD_SINGLE_QUOTE)
		str_builder_add_str(*builder, token->value);
	else
	{
		temp = expand_all_variables_(token->value);
		str_builder_add_str(*builder, temp);
		free(temp);
	}
}

char	*expand_and_join_words(t_dlist **tokens)
{
	t_token			*token;
	t_str_builder	*builder;
	char			*result;

	if (!tokens || !*tokens)
		return (NULL);
	token = (*tokens)->content;
	builder = NULL;
	while (token->id == TD_WORD || token->id == TD_SINGLE_QUOTE
		|| token->id == TD_DOUBLE_QUOTE)
	{
		expand_and_add_to_builder(&builder, token);
		*tokens = (*tokens)->next;
		if (!*tokens)
			break ;
		token = (*tokens)->content;
	}
	if (builder)
	{
		result = ft_strdup(builder->str);
		str_builder_destroy(builder);
		return (result);
	}
	return (NULL);
}
