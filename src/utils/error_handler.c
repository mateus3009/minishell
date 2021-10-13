/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:12:59 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/13 14:13:26 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *cmd, char *err_msg, int err_number)
{
	t_str_builder	*builder;
	char			*prompt_error;

	builder = str_builder_init();
	str_builder_add_str(builder, "minishell : ");
	str_builder_add_str(builder, cmd);
	str_builder_add_str(builder, " : ");
	str_builder_add_str(builder, err_msg);
	prompt_error = ft_strdup(builder->str);
	str_builder_destroy(builder);
	ft_putendl_fd(prompt_error, 2);
	free(prompt_error);
	g_minishell.error_status = err_number;
}
