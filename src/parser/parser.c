/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:23:17 by lniehues          #+#    #+#             */
/*   Updated: 2021/09/22 21:43:28 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	parse(t_dlist *tokens)
{
	t_token	*token;
	char	*new;

	while (tokens)
	{
		token = (t_token *)tokens->content;
		if (token->id == TD_WORD || token->id == TD_DOUBLE_QUOTE)
		{
			new = expand_variable(token->value);
			free(token->value);
			token->value = new;
		}
		printf("<%d, %s>\n", token->id, token->value);
		tokens = tokens->next;
	}
}

/* TODO
*	- separate expand_variable from parse function
*	- create commands array
*	- check if it's builtin
*	- if not, pass it to execve with cmd path, cmd+arguments and env
*/

