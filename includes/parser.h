/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:25:50 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/09 00:09:01 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./../libs/libft/srcs/includes/libft.h"

t_dlist	*next_word_token(t_dlist *token);
t_token	*previous_token_non_space(t_dlist *token);

char	*join_words(t_dlist **tokens);

bool	local_variables_parser(t_dlist **new, t_dlist **tokens);
bool	here_document_parser(t_dlist **new, t_dlist **tokens);
bool	expand_variables_parser(t_dlist **new, t_dlist **tokens);
bool	word_parser(t_dlist **new, t_dlist **tokens);
bool	space_parser(t_dlist **new, t_dlist **tokens);
bool	redirects_parser(t_dlist **new, t_dlist **tokens);

void	parse(t_dlist **ptr_tokens);
void	show_tokens(t_dlist **ptr_tokens);

char	*heredoc(char *value);

#endif
