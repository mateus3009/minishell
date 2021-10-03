/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:33:58 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/03 18:19:31 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_hashmap_item(t_hashmap_item *item)
{
	free(item->value);
	free(item->key);
	free(item);
}

void	free_hashmap_bucket(t_hashmap *bucket)
{
	unsigned int	index;
	t_hashmap_item		*current;
	t_hashmap_item		*temp;

	index = 0;
	while (index < bucket->size)
	{
		current = bucket->items[index];
		while (current)
		{
			temp = current->next;
			free_hashmap_item(current);
			current = temp;
		}
		index++;
	}
	free(bucket->items);
	free(bucket);
}
