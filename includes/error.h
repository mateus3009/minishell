/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:46:31 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/28 21:03:26 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define ERR_NOT_FOUND "command not found"
# define ERR_IS_DIR "Is a directory"
# define TOO_MANY_ARGS "too many arguments"
# define NUM_ARG_REQUIRED "numeric argument required"

void	error_handler(char *cmd, char *err_msg, int err_number);

#endif
