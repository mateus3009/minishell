/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 12:20:42 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/09 12:21:47 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOCUMENT_H
# define HERE_DOCUMENT_H

# include "./../libs/libft/srcs/includes/libft.h"

char	*heredoc(char *value);
void	here_document_parser(t_dlist **tokens);

#endif
