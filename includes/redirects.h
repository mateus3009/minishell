/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:07:03 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 19:09:10 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

#include "minishell.h"

void	append_mode_redirect(char *value);
void	here_document_redirect(char *value);
void	input_redirect(char *value);
void	output_redirect(char *value);

#endif
