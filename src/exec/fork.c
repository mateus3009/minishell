/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:50:20 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/22 20:56:56 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int main(void)
{
    int     value;
    int     fd[2];
    pid_t   pid;

    value = 0;
    if (pipe(fd) == -1)
        return (EXIT_FAILURE);
    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);
    if (pid == 0) {
        if (read(fd[0], &value, sizeof(int)) == -1)
            return (EXIT_FAILURE);
        printf("readed value: %d\n", value);
    }
    else {
        value = 42;
        if (write(fd[1], &value, sizeof(int)) == -1)
            return (EXIT_FAILURE);
        printf("writed value: %d\n", value);
       wait(NULL);
    }
    return (EXIT_SUCCESS);
}
*/

void	run_system_cmd(char *cmd_path, char *const argv[], char *const env[])
{
	int		status;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		printf("%s", strerror(11));
		exit(11);
	}
	else if (child_pid == 0)
	{
		if (execve(cmd_path, argv, env) < 0)
		{
			printf("minishell : %s : %s\n", strerror(errno), cmd_path);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			printf("Exit status: %d\n", WEXITSTATUS(status));
	}
}
