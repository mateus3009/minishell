/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 10:12:07 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/18 13:43:12 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_definition	*init_token_definition(t_token_definition *td)
{
	t_token_definition	*token;

	token = malloc(sizeof(t_token_definition));
	if (!token)
		exit(EXIT_FAILURE);
	token->id = td->id;
	token->open = NULL;
	if (td->open)
		token->open = ft_strdup(td->open);
	token->open_size = ft_strlen(td->open);
	token->close = NULL;
	if (td->close)
		token->close = ft_strdup(td->close);
	token->close_size = ft_strlen(td->close);
	token->children = td->children;
	return (token);
}

void	display_token_definition(t_token_definition *td)
{
	printf("id:\t%d\n", td->id);
	printf("id:\t%s\n", td->open);
	printf("id:\t%d\n", td->open_size);
	printf("id:\t%s\n", td->close);
	printf("id:\t%d\n", td->close_size);
	printf("id:\t%d\n", td->children);
}

void	free_token_definition(t_token_definition *td)
{
	if (td->open)
		free(td->open);
	if (td->close)
		free(td->close);
	free(td);
}

t_token_definition	*init_td_here_string(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_HERE_STRING,
		.open = "<<<",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_append(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_APPEND,
		.open = ">>",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_here_file(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_HERE_FILE,
		.open = "<<",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_and(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_AND,
		.open = "&&",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_or(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_OR,
		.open = "||",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_command(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_COMMAND,
		.open = "$(",
		.close = ")",
		.children = TD_ALL
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_variable(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_VARIABLE,
		.open = "${",
		.close = "}",
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_space(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_SPACE,
		.open = " ",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_pipe(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_PIPE,
		.open = "|",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_output(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_OUTPUT,
		.open = ">",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_input(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_INTPUT,
		.open = "<",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_variable2(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_VARIABLE2,
		.open = "$",
		.close = NULL,
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_command2(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_COMMAND2,
		.open = "`",
		.close = "`",
		.children = TD_ALL
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_single_quote(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_SINGLE_QUOTE,
		.open = "'",
		.close = "'",
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_double_quote(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_DOUBLE_QUOTE,
		.open = "\"",
		.close = "\"",
		.children = TD_ALL ^ TD_SINGLE_QUOTE
	};
	return (init_token_definition(&token));
}

t_token_definition	*init_td_parentheses(void)
{
	t_token_definition	token;

	token = (t_token_definition){
		.id = TD_PARENTHESES,
		.open = "(",
		.close = ")",
		.children = TD_NONE
	};
	return (init_token_definition(&token));
}

t_token_definition	**init_all_token_definition(void)
{
	int					index;
	t_token_definition	**token;
	t_td_initalizer		*initializers;

	index = 17;
	token = malloc(sizeof(t_token_definition *) * index);
	initializers = (t_td_initalizer[]){init_td_here_string, init_td_append,
		init_td_here_file, init_td_and, init_td_or, init_td_command,
		init_td_variable, init_td_space, init_td_pipe, init_td_output,
		init_td_input, init_td_variable2, init_td_command2, init_td_single_quote,
		init_td_double_quote, init_td_parentheses, NULL};
	index = -1;
	while (initializers[++index])
		token[index] = initializers[index]();
	token[index] = NULL;
	return (token);
}
