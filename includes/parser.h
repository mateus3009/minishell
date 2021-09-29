/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:25:50 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/28 20:58:20 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./../libs/libft/srcs/includes/libft.h"

void	parse(t_dlist **ptr_tokens);
void	expand_token_variables(t_token *token);
char	**create_command(t_dlist *head, t_dlist *end_or_pipe);
char	*expand_all_variables(char *str);
void	parse_expand_all_variables(t_dlist **ptr_tokens);
void	join_word(t_dlist **ptr_tokens);
void	show_tokens(t_dlist **ptr_tokens);
void	parse_here_document(t_dlist **ptr_tokens);
char	*find_command_path(char *path, char *command);

#endif
