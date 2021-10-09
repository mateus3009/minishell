/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:25:50 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/09 12:22:47 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./../libs/libft/srcs/includes/libft.h"

typedef	int (* t_token_parser)(t_dlist **new, t_dlist **tokens);

char	*join_words(t_dlist **tokens);
int		common_parser(t_dlist **new, t_dlist **tokens);
void	parser_core(t_dlist **tokens, t_token_parser *parsers);
void	show_tokens(t_dlist **ptr_tokens);

#endif
