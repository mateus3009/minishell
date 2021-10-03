/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:59:57 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/03 18:24:18 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include "minishell.h"

typedef struct s_hashmap_item
{
	char					*key;
	char					*value;
	struct s_hashmap_item	*next;
}				t_hashmap_item;

typedef struct s_hashmap
{
	t_hashmap_item	**items;
	unsigned int	count;
	unsigned int	size;
}				t_hashmap;

/*
**	MAIN
*/
unsigned long int	hash(char *key, unsigned int size);
void				handle_hashmap_collision(
						t_hashmap *bucket,
						unsigned long int index,
						t_hashmap_item *new_item);

/*
**	CREATE
*/
t_hashmap_item		*create_hashmap_item(char *key, char *value);
t_hashmap			*create_hashmap_bucket(unsigned int size);

/*
**	FREE
*/
void				free_hashmap_item(t_hashmap_item *item);
void				free_hashmap_bucket(t_hashmap *bucket);

/*
**	OPERATIONS
*/
void				insert_on_hashmap(
						char *key,
						char *value,
						t_hashmap *bucket);
void				remove_from_hashmap(t_hashmap *bucket, char *key);
char				*find_hashmap_value(t_hashmap *bucket, char *key);

/*
**	DISPLAY
*/
void				display_hashmap_bucket(t_hashmap *bucket);

#endif