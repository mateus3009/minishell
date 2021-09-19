/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 17:33:24 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/19 17:39:13 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_builder	*token_builder_init(int id)
{
	t_token_builder	*token;

	token = malloc(sizeof(token));
	if (!token)
		return (NULL);
	token->id = id;
	token->builder = str_builder_init();
	return (token);
}

void	token_builder_free(t_token_builder *token_builder)
{
	str_builder_destroy(token_builder->builder);
	free(token_builder);
}
