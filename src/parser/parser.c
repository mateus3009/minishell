/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/25 19:13:31 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO
*	- separate expand_variable from parse function
*	- create commands array
*	- check if it's builtin
*	- if not, pass it to execve with cmd path, cmd+arguments and env
*/

void	parse(t_dlist **ptr_tokens)
{
	char	**cmd;
	char	*path;

	parse_expand_all_variables(ptr_tokens);
	join_word(ptr_tokens);
	parse_here_document(ptr_tokens);
	show_tokens(ptr_tokens);
	cmd = create_command(*ptr_tokens);
	path = find_env(g_minishell.penv, "PATH");
	path = find_command_path(path, cmd[0]);
	free(cmd[0]);
	cmd[0] = path;
	run_system_cmd(cmd);
}
