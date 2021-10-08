/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 07:37:29 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/07 21:28:03 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

# include "minishell.h"

typedef struct s_call
{
	char	*path;
	t_dlist	*argv;
}	t_call;

typedef struct s_command
{
	t_call	call;
	t_dlist	*redirects;
}	t_command;

void	create_pipe(int	**fd);
void	free_pipe(int *fd);
void	configure_reader_pipe(int *fd);
void	configure_writer_pipe(int *fd);

int		run_pipeline(t_list *commands, t_list *operators);
bool	create_pipeline(
			t_dlist *tokens,
			t_list **commands,
			t_list **operators);
void	create_and_run_pipeline(t_dlist *tokens);

void	open_std_fd(void);
void	restore_std_fd(void);
void	close_std_fd(void);


bool	create_command_head(
			t_dlist *tokens,
			t_list **commands,
			t_list **operators);

bool	create_command_arg(
			t_dlist *tokens,
			t_list **commands,
			t_list **operators);

bool	create_redirect(
			t_dlist *tokens,
			t_list **commands,
			t_list **operators);

bool	create_operator(
			t_dlist *tokens,
			t_list **commands,
			t_list **operators);

#endif
