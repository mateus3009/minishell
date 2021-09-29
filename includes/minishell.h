/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:27:00 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/28 21:51:59 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./../libs/libft/srcs/includes/libft.h"
# include "styles.h"
# include "tokens.h"
# include "parser.h"
# include "error.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
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
char			**tpenv_to_array(t_penv	*env);

/*
*	SYSTEM CALLS
*/

void			run_system_cmd(char **cmd_array);
void			excute_command(char **cmd_array);

/*
*	SIGNALS
*/
void			set_input_signals(void);
void			set_exec_signals(void);

/*
*	BUILTINS
*/
bool			is_builtin_cmd(char *value);
void			exit_minishell(void);
void			exit_builtin(char **argv);

/**
 *	UTILS
 */
char			*ft_strrstr(char const *big, const char *little);
void			free_str_array(char **str_array);

#endif
