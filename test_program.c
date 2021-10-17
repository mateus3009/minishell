/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:06:16 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/17 12:28:24 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int	main(int argc, char **argv, char **env)
{
	size_t	index;

	if (argc == 0)
	{
		fprintf(stderr, "Como isso é possível? zero argumentos!?");
		return (1);
	}
	if (!argv || !*argv)
	{
		fprintf(stderr, "Como isso é possível? argumentos nulos!?");
		return (1);
	}
	if (!env || !*env)
	{
		fprintf(stderr, "Como isso é possível? environment nulo!?");
		return (1);
	}
	index = -1;
	printf("environment:\n");
	while (env[++index])
		printf("%s\n", env[index]);
	index = -1;
	printf("\nargumentos:\n");
	while (argv[++index])
		printf("%s\n", argv[index]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	printf("Mate o programa antes do fim da frase!\n");
	sleep(1);
	setbuf(stdout, NULL);
	printf("Ba");
	sleep(1);
	printf("ta");
	sleep(1);
	printf("tinha ");
	sleep(2);
	printf("frita ");
	sleep(1);
	printf("1");
	sleep(1);
	printf(", 2");
	sleep(2);
	printf(", 3\n");
	fprintf(stderr, "Eliminado!\n");
	raise(SIGSEGV);
	return (0);
}
