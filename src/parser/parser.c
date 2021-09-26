/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/26 18:28:16 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO
*	- separate expand_variable from parse function
*	- create commands array
*	- check if it's builtin
*	- if not, pass it to execve with cmd path, cmd+arguments and env
*/

void	error_handler(char *cmd, char *err_msg, int err_number)
{
	t_str_builder	*builder;
	char			*prompt_error;

	builder = str_builder_init();
	str_builder_add_str(builder, "minishell : ");
	str_builder_add_str(builder, cmd);
	str_builder_add_str(builder, " : ");
	str_builder_add_str(builder, err_msg);
	prompt_error = ft_strdup(builder->str);
	str_builder_destroy(builder);
	ft_putendl_fd(prompt_error, 2);
	free(prompt_error);
	g_minishell.error_status = err_number;
}

static int	cmd_errno(char *cmd_path)
{
	struct stat	buffer;

	if (stat(cmd_path, &buffer) != 0)
		return (127);
	if (buffer.st_mode & __S_IFMT & __S_IFDIR)
		return (126);
	return (0);
}

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
	if (path)
	{
		free(cmd[0]);
		cmd[0] = path;
		run_system_cmd(cmd);
	}
	else
	{
		int err = cmd_errno(cmd[0]);
		if (err == 127)
			error_handler(cmd[0], ERR_NOT_FOUND, err);
		else if (err == 126)
			error_handler(cmd[0], ERR_IS_DIR,err);
	}
	free_str_array(cmd);
}
echo | alguma << coisa | alguma outra coisa > teste

[<'<', 2, teste>, <0, echo>]
