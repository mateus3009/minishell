/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:25:50 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/25 16:46:39 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./../libs/libft/srcs/includes/libft.h"

void	parse(t_dlist **ptr_tokens);
void	expand_token_variables(t_token *token);
char	**create_command(t_dlist *tokens);
char	*expand_all_variables(char *str);
void	parse_expand_all_variables(t_dlist **ptr_tokens);
void	join_word(t_dlist **ptr_tokens);
void	show_tokens(t_dlist **ptr_tokens);
void	parse_here_document(t_dlist **ptr_tokens);

#endif
