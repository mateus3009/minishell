/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/25 16:42:05 by lniehues         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO
*	- separate expand_variable from parse function
*	- create commands array
*	- check if it's builtin
*	- if not, pass it to execve with cmd path, cmd+arguments and env
*/

static size_t	env_length(t_penv *env)
{
	size_t	len;

	len = 0;
	while (env[len].key)
		len++;
	return (len);
}

static char	*parse_penv_to_char(t_penv *env)
{
	size_t	key;
	size_t	value;
	char	*result;

	key = ft_strlen(env->key);
	value = ft_strlen(env->value);
	result = malloc(sizeof(char) * (key + value + 2));
	if (!result)
		return (NULL);
	result[key] = '=';
	result[key + value + 1] = '\0';
	ft_memmove(result, env->key, key);
	ft_memmove(result + key + 1, env->value, value);
	return (result);
}

char	**tpenv_to_array(t_penv	*env)
{
	char	**env_array;
	int		len;
	int		i;

	len = env_length(env);
	env_array = malloc(sizeof(char *) * (len + 1));
	env_array[len] = NULL;
	i = -1;
	while (env[++i].key)
		env_array[i] = parse_penv_to_char(&env[i]);
	return (env_array);
}

void	expand_all_variables(t_dlist **ptr_tokens)
{
	t_dlist	*tokens;
	t_token	*token;
	char	*new;
	int		len;

	tokens = *ptr_tokens;
	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->id == TD_WORD || token->id == TD_DOUBLE_QUOTE)
		{
			while (find_variable(token->value, &len))
			{
				new = expand_variable(token->value);
				free(token->value);
				token->value = new;
			}
		}
		tokens = tokens->next;
	}
}

char	*here_document(char *value)
{
	t_str_builder	*builder;
	char			*line;

	builder = str_builder_init();
	while (true)
	{
		line = readline("> ");
		if (!line)
			return ((str_builder_destroy(builder), NULL));
		if (ft_strcmp(value, line) == 0)
			break ;
		str_builder_add_str(builder, line);
		free(line);
	}
	line = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (line);
}

static void	join_word_node(
	t_dlist **tokens,
	t_token *token,
	t_str_builder **builder)
{
	if (token->id == TD_WORD || token->id == TD_SINGLE_QUOTE
		|| token->id == TD_DOUBLE_QUOTE)
	{
		if (!*builder)
			*builder = str_builder_init();
		str_builder_add_str(*builder, token->value);
		return ;
	}
	if (*builder)
	{
		add_token_to_result(tokens, TD_WORD, (*builder)->str);
		str_builder_destroy(*builder);
		*builder = NULL;
	}
	add_token_to_result(tokens, token->id, token->value);
}

void	join_word(t_dlist **ptr_tokens)
{
	t_dlist			*tokens;
	t_dlist			*new_tokens;
	t_str_builder	*builder;

	tokens = *ptr_tokens;
	new_tokens = NULL;
	builder = NULL;
	while (tokens)
	{
		join_word_node(&new_tokens, tokens->content, &builder);
		tokens = tokens->next;
	}
	if (builder)
	{
		add_token_to_result(&new_tokens, TD_WORD, builder->str);
		str_builder_destroy(builder);
	}
	ft_dlstclear(ptr_tokens, token_free);
	*ptr_tokens = new_tokens;
}

void	show_tokens(t_dlist **ptr_tokens)
{
	t_dlist				*tokens;
	t_token				*token;
	t_token_definition	*def;
	int					index;

	def = (t_token_definition[]){
	{.id = TD_HERE_DOCUMENT, .value = "<<"}, {.id = TD_AND, .value = "&&"},
	{.id = TD_OR, .value = "||"}, {.id = TD_APPEND_MODE, .value = ">>"},
	{.id = TD_PIPE, .value = "|"}, {.id = TD_INPUT, .value = ">"},
	{.id = TD_OUTPUT, .value = "<"}, {.id = TD_DOUBLE_QUOTE, .value = "\""},
	{.id = TD_SINGLE_QUOTE, .value = "'"}, {.id = TD_SPACE, .value = " "},
	{.id = 0, .value = NULL}};
	tokens = *ptr_tokens;
	while (tokens)
	{
		index = 0;
		token = (t_token *)tokens->content;
		while (token->id && def[index].id && token->id != def[index].id)
			index++;
		printf("<%d, ", token->id);
		if (token->id)
			printf("%s>\n", def[index].value);
		else
			printf("%s>\n", token->value);
		tokens = tokens->next;
	}
}

void	parse(t_dlist **ptr_tokens)
{
	char	**cmd;
	char	**env;

	expand_all_variables(ptr_tokens);
	join_word(ptr_tokens);
	show_tokens(ptr_tokens);
	cmd = create_command(*ptr_tokens);
	env = tpenv_to_array(g_minishell.penv);
	run_system_cmd(cmd[0], cmd, env);
}
