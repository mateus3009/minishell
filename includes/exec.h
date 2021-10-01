/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:48:54 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/30 22:08:56 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

pid_t	execute_command(t_command *command);
pid_t	execute_call(t_call	call);
void	execute_redirect(t_redirect redirect);

#endif
