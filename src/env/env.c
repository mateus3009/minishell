/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:26:18 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/25 10:49:26 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_penv	*parse_env(char *const env[])
{
	int		i;
	t_penv	*parsed_env;
	char	*equal;
	char	*tmp;

	i = 0;
	while (env[i])
		i++;
	parsed_env = malloc(sizeof(t_penv) * (i + 1));
	if (!parsed_env)
		exit(1);
	parsed_env[i] = (t_penv){.key = NULL, .value = NULL};
	i = -1;
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		equal = ft_strchr(tmp, '=');
		tmp[equal - tmp] = '\0';
		parsed_env[i].key = tmp;
		parsed_env[i].value = equal + 1;
	}
	return (parsed_env);
}

void	display_env(t_penv *penv)
{
	int	i;

	i = -1;
	while (penv[++i].key)
		printf("%s=%s\n", penv[i].key, penv[i].value);
}

char	*find_env(t_penv *penv, char *key)
{
	if (*key == '?')
		return (ft_itoa(g_minishell.error_status));
	while (penv->key)
	{
		if (ft_strcmp(penv->key, key) == 0)
			return (penv->value);
		penv++;
	}
	return (NULL);
}

void	free_env(t_penv *penv)
{
	int	index;

	index = -1;
	while (penv[++index].key)
		free(penv[index].key);
	free(penv);
}

static size_t	env_length(t_penv *env)
{
	size_t	len;

	len = 0;
	while (env[len].key)
		len++;
	return (len);
}

static char	*parse_penv_to_char(t_penv *env)
{
	size_t	key;
	size_t	value;
	char	*result;

	key = ft_strlen(env->key);
	value = ft_strlen(env->value);
	result = malloc(sizeof(char) * (key + value + 2));
	if (!result)
		return (NULL);
	result[key] = '=';
	result[key + value + 1] = '\0';
	ft_memmove(result, env->key, key);
	ft_memmove(result + key + 1, env->value, value);
	return (result);
}

char	**tpenv_to_array(t_penv	*env)
{
	char	**env_array;
	int		len;
	int		i;

	len = env_length(env);
	env_array = malloc(sizeof(char *) * (len + 1));
	env_array[len] = NULL;
	i = -1;
	while (env[++i].key)
		env_array[i] = parse_penv_to_char(&env[i]);
	return (env_array);
}
