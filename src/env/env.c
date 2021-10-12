/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:24:32 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/12 17:34:25 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_hashmap *env)
{
	unsigned int	index;
	t_hashmap_item	*current;

	index = 0;
	while (index < env->size)
	{
		current = env->items[index];
		while (current)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(current->value, 1);
			current = current->next;
		}
		index++;
	}
}

char	*find_env(char *key)
{
	if (*key == '?')
		return (ft_itoa(g_minishell.error_status));
	return (find_hashmap_value(g_minishell.env, key));
}

t_hashmap	*env_to_hashmap(char *const env[])
{
	int			i;
	t_hashmap	*parsed_env;
	char		*equal;
	char		*tmp;

	i = 0;
	while (env[i])
		i++;
	parsed_env = create_hashmap_bucket(i * 2);
	i = -1;
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		equal = ft_strchr(tmp, '=');
		tmp[equal - tmp] = '\0';
		insert_on_hashmap(tmp, equal + 1, parsed_env);
		free(tmp);
	}
	return (parsed_env);
}

static char	*item_to_env_entry(t_hashmap_item *item)
{
	char	*entry;
	char	*temp;

	temp = ft_strjoin(item->key, "=");
	entry = ft_strjoin(temp, item->value);
	free(temp);
	return (entry);
}

char	**hashmap_env_to_array_env(t_hashmap *bucket)
{
	unsigned int	i;
	unsigned int	j;
	t_hashmap_item	*current;
	t_hashmap_item	*temp;
	char			**env;

	i = 0;
	j = 0;
	env = (char **)ft_calloc(sizeof (char *), bucket->count + 1);
	while (i < bucket->size && j < bucket->count)
	{
		current = bucket->items[i];
		while (current != NULL)
		{
			temp = current->next;
			env[j] = item_to_env_entry(current);
			current = temp;
			j++;
		}
		i++;
	}
	return (env);
}
