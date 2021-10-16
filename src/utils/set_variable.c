/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:30:38 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/16 10:36:37 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_variable(char *keyvalue, t_hashmap *ht)
{
	char	**parts;
	char	*value;

	if (!keyvalue || !ht)
		return ;
	parts = ft_split(keyvalue, '=');
	if (!parts)
		exit_minishell();
	value = find_hashmap_value(ht, parts[0]);
	if (!value || (ft_strchr(keyvalue, '=') && value))
		insert_on_hashmap(parts[0], parts[1], ht);
	free(value);
	free_str_array(parts);
}
