/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:50:20 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 19:16:22 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_redirect(t_redirect redirect)
{
	if (redirect.type == TD_INPUT)
		input_redirect(redirect.value);
	if (redirect.type == TD_HERE_DOCUMENT)
		here_document_redirect(redirect.value);
	if (redirect.type == TD_OUTPUT)
		output_redirect(redirect.value);
	if (redirect.type == TD_APPEND_MODE)
		append_mode_redirect(redirect.value);
	exit_minishell();
}
