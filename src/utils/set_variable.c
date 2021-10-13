/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:30:38 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/12 20:18:01 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_variable(char *keyvalue, t_hashmap *ht)
{
	char	**parts;

	if (!keyvalue || !ht)
		return ;
	parts = ft_split(keyvalue, '=');
	if (!parts)
		exit_minishell();
	insert_on_hashmap(parts[0], parts[1], ht);
	free_str_array(parts);
}
