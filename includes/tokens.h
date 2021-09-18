/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:43:35 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/18 14:13:49 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

/**
 *
 * HERE_STRING	<<<	NULL	1		1 << 0
 * APPEND		>>	NULL	2		1 << 1
 * HERE_FILE	<<	NULL	4		1 << 2
 * AND			&&	NULL	8		1 << 3
 * OR			||	NULL	16		1 << 4
 * COMMAND		$(	)		32		1 << 5
 * VARIABLE		${	}		64		1 << 6
 * SPACE		 	NULL	128		1 << 7
 * PIPE			|	NULL	256		1 << 8
 * OUTPUT		>	NULL	512		1 << 9
 * INTPUT		<	NULL	1024	1 << 10
 * VARIABLE2	$	NULL	2048	1 << 11
 * COMMAND2		`	`		4096	1 << 12
 * SINGLE_QUOTE	'	'		8192	1 << 13
 * DOUBLE_QUOTE	"	"		16384	1 << 14
 * PARENTHESES	(	)		32768	1 << 15
 *
 */

# define TD_NONE				 0
# define TD_ALL					~0
# define TD_HERE_STRING		1 << 0
# define TD_APPEND			1 << 1
# define TD_HERE_FILE		1 << 2
# define TD_AND				1 << 3
# define TD_OR				1 << 4
# define TD_COMMAND			1 << 5
# define TD_VARIABLE		1 << 6
# define TD_SPACE			1 << 7
# define TD_PIPE			1 << 8
# define TD_OUTPUT			1 << 9
# define TD_INTPUT			1 << 10
# define TD_VARIABLE2		1 << 11
# define TD_COMMAND2		1 << 12
# define TD_SINGLE_QUOTE	1 << 13
# define TD_DOUBLE_QUOTE	1 << 14
# define TD_PARENTHESES		1 << 15

typedef struct s_token_definition
{
	unsigned short		id;
	char				*open;
	unsigned short		open_size;
	char				*close;
	unsigned short		close_size;
	unsigned int		children;
}	t_token_definition;

typedef struct s_token
{
	t_token_definition	*token;
	char				*value;
}				t_token;

typedef t_token_definition	*(*	t_td_initalizer)(void);

t_token_definition	*init_token_definition(t_token_definition *td);
void				display_token_definition(t_token_definition *td);
void				free_token_definition(t_token_definition *td);
t_token_definition	*init_td_here_string(void);
t_token_definition	*init_td_append(void);
t_token_definition	*init_td_here_file(void);
t_token_definition	*init_td_and(void);
t_token_definition	*init_td_or(void);
t_token_definition	*init_td_command(void);
t_token_definition	*init_td_variable(void);
t_token_definition	*init_td_space(void);
t_token_definition	*init_td_pipe(void);
t_token_definition	*init_td_output(void);
t_token_definition	*init_td_input(void);
t_token_definition	*init_td_variable2(void);
t_token_definition	*init_td_command2(void);
t_token_definition	*init_td_single_quote(void);
t_token_definition	*init_td_double_quote(void);
t_token_definition	*init_td_parentheses(void);
t_token_definition	**init_all_token_definition(void);

#endif
