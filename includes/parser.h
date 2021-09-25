/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:25:50 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/25 18:50:40 by msales-a         ###   ########.fr       */
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
char	*find_command_path(char *path, char *command);

#endif
