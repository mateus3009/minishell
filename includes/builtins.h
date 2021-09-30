/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:25:11 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 18:32:34 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

# include "minishell.h"

void	exit_builtin(char **argv);
void	cd_builtin(void);
void	echo_builtin(void);
void	env_builtin(void);
void	export_builtin(void);
void	pwd_builtin(void);
void	unset_builtin(void);

#endif
