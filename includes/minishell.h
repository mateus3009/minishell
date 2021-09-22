/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:27:00 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/21 21:42:52 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libs/libft/srcs/includes/libft.h"
# include "styles.h"
# include "tokens.h"
# include "parser.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

typedef struct s_penv
{
	char			*key;
	char			*value;
}				t_penv;

typedef struct s_minishell
{
	t_penv	*penv;
	int		error_status;
}				t_minishell;

/* GLOBAL VARIABLE */
t_minishell	g_minishell;

/*
*	ENV
*/

t_penv			*parse_env(char *const env[]);
void			display_env(t_penv *penv);
char			*find_env(t_penv *penv, char *key);
void			free_env(t_penv *penv);

/*
*	SYSTEM CALLS
*/

void			run_system_cmd(
					char *cmd_path,
					char *const argv[],
					char *const env[]);

/*
*	SIGNALS
*/
void			set_input_signals(void);

/*
*	BUILTINS
*/
void			exit_minishell(void);

#endif
