/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_constructor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 07:46:22 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/04 18:42:44 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	create_command_head(
				t_dlist *tokens,
				t_list **commands,
				t_list **operators);

static bool	create_command_arg(
				t_dlist *tokens,
				t_list **commands,
				t_list **operators);

static bool	create_redirect(
				t_dlist *tokens,
				t_list **commands,
				t_list **operators);

static bool	create_operator(
				t_dlist *tokens,
				t_list **commands,
				t_list **operators);

static bool	create_command_head(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token		*token;
	t_command	*command;
	t_list		*node;

	if (!tokens)
		return (false);
	token = tokens->content;
	if (token->id != TD_WORD)
		return (false);
	command = ft_calloc(1, sizeof(t_command));
	command->call.path = find_command_path(
			find_env(g_minishell.penv, "PATH"), token->value);
	command->call.argv = ft_dlstnew(ft_strdup(token->value));
	node = ft_lstnew(command);
	if (!node || !node->content)
		exit_minishell();
	ft_lstadd_back(commands, node);
	return (create_command_arg(tokens->next, commands, operators)
		|| create_redirect(tokens->next, commands, operators)
		|| create_operator(tokens->next, commands, operators));
}

static bool	create_command_arg(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token		*token;
	t_command	*command;
	t_dlist		*node;

	if (!tokens)
		return (true);
	token = tokens->content;
	if (token->id != TD_WORD)
		return (false);
	command = ft_lstlast(*commands)->content;
	node = ft_dlstnew(ft_strdup(token->value));
	if (!node || !node->content)
		exit_minishell();
	ft_dlstadd_back(&(command->call.argv), node);
	return (create_command_arg(tokens->next, commands, operators)
		|| create_redirect(tokens->next, commands, operators)
		|| create_operator(tokens->next, commands, operators));
}

static bool	create_redirect(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token		*token;
	t_command	*command;
	t_dlist		*node;

	if (!tokens)
		return (true);
	token = tokens->content;
	if (token->id != TD_INPUT && token->id != TD_OUTPUT
		&& token->id != TD_APPEND_MODE && token->id != TD_HERE_DOCUMENT)
		return (false);
	command = ft_lstlast(*commands)->content;
	node = ft_dlstnew(token_init(token->id, token->value));
	if (!node || !node->content)
		exit_minishell();
	ft_dlstadd_back(&(command->redirects), node);
	return (create_redirect(tokens->next, commands, operators)
		|| create_operator(tokens->next, commands, operators));
}

static bool	create_operator(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	t_token	*token;
	int		*number;
	t_list	*node;

	if (!tokens)
		return (true);
	token = tokens->content;
	if (token->id != TD_PIPE && token->id != TD_AND && token->id != TD_OR)
		return (false);
	number = malloc(sizeof(int));
	if (!number)
		exit_minishell();
	*number = token->id;
	node = ft_lstnew(number);
	if (!node)
		exit_minishell();
	ft_lstadd_back(operators, node);
	return (create_command_head(tokens->next, commands, operators));
}

bool	create_pipeline(
	t_dlist *tokens,
	t_list **commands,
	t_list **operators)
{
	return (create_command_head(tokens, commands, operators));
}
