/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:26:18 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/25 19:13:29 by msales-a         ###   ########.fr       */
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

char	*ft_strstr(char const *haystack, const char *needle) // TODO mover para libft
{
	size_t	needle_size;
	size_t	haystack_size;

	if (!*needle || !haystack)
		return ((char *)haystack);
	needle_size = ft_strlen(needle);
	haystack_size = ft_strlen(haystack);
	while (*haystack && needle_size <= haystack_size)
	{
		if (ft_strncmp(haystack, needle, needle_size) == 0)
			return ((char *)haystack);
		haystack++;
		haystack_size--;
	}
	return (NULL);
}

char	*find_command_path(char *path, char *command)
{
	char	*finded;
	size_t	size;

	if (!path || !command)
		return (NULL);
	finded = path;
	size = ft_strlen(command);
	while (true)
	{
		finded = strstr(finded, command);
		if (!finded)
			return (NULL);
		if (finded[size] == ':' || finded[size] == '\0')
			break ;
		finded++;
	}
	while (finded != path && *finded != ':')
		finded--;
	size = ft_strchr(finded, ':') - finded;
	return (ft_strndup(finded, size));
}
