/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:33:20 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/03 18:19:29 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hashmap	*create_hashmap_bucket(unsigned int size)
{
	t_hashmap		*new_bucket;
	unsigned int	index;

	index = 0;
	new_bucket = ft_calloc(sizeof(t_hashmap), 1);
	new_bucket->size = size;
	new_bucket->count = 0;
	new_bucket->items = ft_calloc(sizeof(t_hashmap_item), size);
	while (index < size)
		new_bucket->items[index++] = NULL;
	return (new_bucket);
}

t_hashmap_item	*create_hashmap_item(char *key, char *value)
{
	t_hashmap_item	*new_item;

	new_item = ft_calloc(sizeof(t_hashmap_item), 1);
	new_item->key = ft_strdup(key);
	new_item->value = ft_strdup(value);
	return (new_item);
}
