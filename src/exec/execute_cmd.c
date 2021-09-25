/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:50:20 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/25 19:13:32 by msales-a         ###   ########.fr       */
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

void run_system_cmd(char **cmd_array)
{
	int status;
	pid_t child_pid;
	char **env_array;

	if (!cmd_array[0])
		return ;
	child_pid = fork();
	set_exec_signals();
	if (child_pid == 0)
	{
		env_array = tpenv_to_array(g_minishell.penv);
		execve(cmd_array[0], cmd_array, env_array);
		free_penv_array(env_array);
	}
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
	{
		printf("Exit status: %d\n", WEXITSTATUS(status));
		g_minishell.error_status = WEXITSTATUS(status);
	}
}
