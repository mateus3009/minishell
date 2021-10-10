/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:29:28 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/10 14:19:46 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_free(t_command *command)
{
	if (!command)
		return ;
	ft_dlstclear(&command->words, free);
	ft_dlstclear(&command->variables, free);
	ft_dlstclear(&command->redirects, token_free);
	free(command);
}

t_command	*command_init(void)
{
	return (ft_calloc(1, sizeof(t_command)));
}

void	command_show(t_command *command) // TODO remover isso aqui
{
	t_dlist	*temp;

	if (!command)
		return ;
	if (command->op)
		printf("operator: %d\n", command->op);
	else
		printf("operator: não tem cara\n");
	printf("variables:\n");
	temp = command->variables;
	while (temp)
	{
		printf("\t- %s\n", temp->content);
		temp = temp->next;
	}
	printf("words:\n");
	temp = command->words;
	while (temp)
	{
		printf("\t- %s\n", temp->content);
		temp = temp->next;
	}
	printf("redirects:\n");
	temp = command->redirects;
	while (temp)
	{
		printf("\t- %d:%s\n",
			((t_token *)temp->content)->id, ((t_token *)temp->content)->value);
		temp = temp->next;
	}
}
