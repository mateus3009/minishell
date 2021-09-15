/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:50:27 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/14 21:47:10 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char    *line;

    line = NULL;
    do
    {
        line = readline(NULL);
        if (!line)
            break ;
		printf("O que você escreveu: %s\n", line);
		add_history(line);
		free(line);
    } while (true);
    printf("\nEOF\n");
	rl_clear_history();
    return (0);
}
