/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/25 16:48:07 by lniehues         ###   ########.fr       */
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
	char	**env;

	parse_expand_all_variables(ptr_tokens);
	join_word(ptr_tokens);
	parse_here_document(ptr_tokens);
	show_tokens(ptr_tokens);
	cmd = create_command(*ptr_tokens);
	env = tpenv_to_array(g_minishell.penv);
	run_system_cmd(cmd[0], cmd, env);
}
