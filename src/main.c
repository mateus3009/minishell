/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/18 14:57:43 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_list_children(t_token_definition **tokens, unsigned int children)
{
	int	index;

	index = 0;
	while (tokens[index])
	{
		if (tokens[index]->id & children)
			printf("id: %d, open: %s\n",
				tokens[index]->id , tokens[index]->open);
		index++;
	}
}

void	testa_token(t_token_definition *token, char *str, int *index)
{
	// verificar se encontrou o token ' ' ' ola'
	if (strncmp(token->open, str + *index, token->open_size) != 0)
		return ;
	if (token->id == TD_SPACE)
		while (ft_isspace(str + *index))
			*index++;

}
{
	type = $
	value =
}
ec$cho "ho")
/** token atual, str, index
 * para cada letra do string
 * > procura o backslash
 * >> se encontrar -> avanca duas posicoes
 * > procura o fim do token atual
 * >> se não encontrar -> adiciona letra no value do token atual
 * > procura por um token
 * >> se encontrar um token -> adiciona um filho na arvoe -> break
 * > ...
work -> quote
*/
void	tokenizer(char *str)
{
	int		index;
	t_dlist	*token;

	index = 0
	token = NULL; // TODO colocar uma word
	while (str[index])
	{

	}
}
int main()
{
	t_token_definition	**token_types;
	char				*line;

	line = NULL;
	token_types = init_all_token_definition();
	test_list_children(token_types, TD_ALL ^ TD_AND);
	return (0);
	// while (1)
	// {
	// 	line = readline(NULL);
	// 	if (!line || line == "\n")
	// 		break ;
	// 	test_here_file(token_types, line);
	// 	add_history(line);
	// }
	// clear_history();

	line = "ec\"ho \" \"nome\" nome && echo $nome 'nome' \"$nome\" | grep nome > file.txt |";
	return (0);
}
