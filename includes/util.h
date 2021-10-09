/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:14:59 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/09 14:21:09 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "minishell.h"

char	*ft_strrstr(char const *big, const char *little);
void	free_str_array(char **str_array);
void	exit_minishell(void);
char	**str_list_array(t_dlist *args);
void	copy_buffer(int from_fd, int to_fd);
void	open_std_fd(void);
void	restore_std_fd(void);
void	close_std_fd(void);

#endif