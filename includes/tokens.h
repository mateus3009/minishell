/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 16:02:57 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/05 08:18:04 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "./../libs/libft/srcs/includes/libft.h"

# define TD_WORD			0
# define TD_HERE_DOCUMENT	1
# define TD_AND				2
# define TD_OR				3
# define TD_APPEND_MODE		4
# define TD_SPACE			5
# define TD_SINGLE_QUOTE	6
# define TD_DOUBLE_QUOTE	7
# define TD_PIPE			8
# define TD_INPUT			9
# define TD_OUTPUT			10
# define TD_VARIABLE		11

typedef struct s_token_definition
{
	short	id;
	char	*value;
	size_t	length;
}				t_token_definition;

typedef struct s_token_builder
{
	short			id;
	t_str_builder	*builder;
}				t_token_builder;

typedef struct s_token
{
	short	id;
	char	*value;
}				t_token;

t_token_builder	*token_builder_init(int id);
void			token_builder_free(t_token_builder *token_builder);
t_token			*token_init(int id, char *str_to_copy);
void			token_free(void *token);
int				find_token(
					char *str,
					int *index);
int				find_end_quote_token(
					char *str,
					int *index,
					t_token_builder *token);
int				find_end_of_token(
					char *str,
					int *index,
					t_token_builder *token);
void			add_token_to_result(
					t_dlist **tokens,
					int id,
					char *str);
void			add_the_curent_token_id_to_the_result(
					t_dlist **tokens, int id);
void			token_recognition(t_dlist **tokens, char *str);

#endif
