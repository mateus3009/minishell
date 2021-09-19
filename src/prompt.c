#include "minishell.h"

static void	save_history(char *input)
{
	if (input && *input)
		add_history(input);
}

char	*create_prompt(void)
{
	t_str_builder	*builder;
	char			*prompt;

	builder = str_builder_init();
	str_builder_add_str(builder, BOLD_RED);
	str_builder_add_str(builder, find_env(g_minishell.penv, "LOGNAME"));
	str_builder_add_char(builder, '@');
	str_builder_add_str(builder, find_env(g_minishell.penv, "NAME"));
	str_builder_add_char(builder, ':');
	str_builder_add_str(builder, ESC_RESET_COLOR);
	str_builder_add_str(builder, BOLD_PURPLE);
	if (ft_strcmp(find_env(g_minishell.penv, "HOME"),
		find_env(g_minishell.penv, "PWD")) == 0)
		str_builder_add_char(builder, '~');
	else
		str_builder_add_str(builder, find_env(g_minishell.penv, "PWD"));
	str_builder_add_str(builder, ESC_RESET_COLOR);
	str_builder_add_str(builder, "$ ");
	prompt = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (prompt);
}

void	read_input(char **input)
{
	char	*prompt;

	prompt = create_prompt();
	// TODO check input signals
	*input = readline(prompt);
	free(prompt);
	save_history(*input);
}
