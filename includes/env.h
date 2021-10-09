/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:12:04 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/09 14:20:06 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_penv
{
	char	*key;
	char	*value;
}		t_penv;

t_penv	*parse_env(char *const env[]);
void	display_env(t_penv *penv);
char	*find_env(t_penv *penv, char *key);
void	free_env(t_penv *penv);
char	**tpenv_to_array(t_penv	*env);
char	*find_command_path(char *path, char *command);

#endif
