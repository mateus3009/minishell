/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:28:08 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/05 09:44:39 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void configure_and_free_pipes(int *in, int *out)
{
	configure_reader_pipe(in);
	configure_writer_pipe(out);
	free_pipe(in);
	free_pipe(out);
}

static void	execute_redirect(t_token *token)
{
	if (token->id == TD_INPUT)
		input_redirect(token->value);
	if (token->id == TD_HERE_DOCUMENT)
		here_document_redirect(token->value);
	if (token->id == TD_OUTPUT)
		output_redirect(token->value);
	if (token->id == TD_APPEND_MODE)
		append_mode_redirect(token->value);
	exit(0);
}

static void	configure_redirect(int **in, int **out, t_dlist *redirect)
{
	t_token	*token;
	pid_t	pid;

	if (!redirect)
		return ;
	token = redirect->content;
	if (token->id == TD_INPUT || token->id == TD_HERE_DOCUMENT)
		(free_pipe(*out), create_pipe(out));
	else
		(free_pipe(*in), create_pipe(in));
	pid = fork();
	if (pid == -1)
		exit_minishell();
	if (pid == 0)
	{
		configure_and_free_pipes(*in, *out);
		execute_redirect(token);
	}
	configure_redirect(in, out, redirect->next);
}

void	execute_command(t_command *command)
{
	int	*in;
	int *out;

	in = NULL;
	out = NULL;
	configure_redirect(&in, &out, command->redirects);
	configure_and_free_pipes(out, in);
	execute_call(command->call);
}
