/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:46:31 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/26 16:58:49 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

# define ERR_NOT_FOUND "command not found"
# define ERR_IS_DIR "Is a directory"

void	error_handler(char *cmd, char *err_msg, int err_number);

#endif
