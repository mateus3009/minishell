/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:31:27 by lniehues          #+#    #+#             */
/*   Updated: 2021/10/16 20:35:05 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO check input signals */

static void	save_history(char *input)
{
	if (input && *input && !ft_isspace(input[0]))
		add_history(input);
}

char	*create_prompt(void)
{
	t_str_builder	*builder;
	char			*temp;

	builder = str_builder_init();
	str_builder_add_str(builder, BOLD_RED);
	str_builder_add_str(builder, getenv("LOGNAME"));
	str_builder_add_char(builder, '@');
	str_builder_add_str(builder, getenv("NAME"));
	str_builder_add_char(builder, ':');
	str_builder_add_str(builder, ESC_RESET_COLOR);
	str_builder_add_str(builder, BOLD_PURPLE);
	str_builder_add_str(builder, find_env("PWD"));
	str_builder_add_str(builder, ESC_RESET_COLOR);
	str_builder_add_str(builder, "$ ");
	temp = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (temp);
}

static void	check_eof(char *line)
{
	if (line || !g_minishell.interactive)
		return ;
	free(line);
	ft_putstr_fd("exit\n", 1);
	exit_minishell();
}

void	read_input_and_save_history(char **input)
{
	char	*prompt;

	prompt = create_prompt();
	set_input_signals();
	if (g_minishell.interactive)
	{
		*input = readline(prompt);
	}
	else
	{
		if (get_next_line(STDIN_FILENO, input) <= 0)
			exit_minishell();
		if (!ft_strlen(*input))
		{
			free(*input);
			*input = NULL;
		}
	}
	g_minishell.general_line++;
	free(prompt);
	save_history(*input);
	check_eof(*input);
	signal(SIGINT, SIG_IGN);
}
