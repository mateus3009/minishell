/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lniehues <lniehues@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:50:20 by msales-a          #+#    #+#             */
/*   Updated: 2021/09/28 22:15:03 by lniehues         ###   ########.fr       */
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

void	run_system_cmd(char **cmd_array)
{
	int		status;
	pid_t	child_pid;
	char	**env_array;

	if (!cmd_array[0])
		return ;
	child_pid = fork();
	set_exec_signals();
	if (child_pid == 0)
	{
		env_array = tpenv_to_array(g_minishell.penv);
		if (execve(cmd_array[0], cmd_array, env_array) < 0)
		{
			free_str_array(env_array);
			printf("minishell : %s : %s\n", cmd_array[0], strerror(errno));
			exit(errno);
		}
		free_str_array(env_array);
	}
	else {
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status))
		{
			printf("Exhhhit status: %d\n", WEXITSTATUS(status));
			g_minishell.error_status = WEXITSTATUS(status);
		}
	}
}

static void	execute_builtin_cmd(char **cmd_array)
{
	if (ft_strcmp(cmd_array[0], "exit") == 0)
		exit_builtin(cmd_array);
}

bool	is_builtin_cmd(char *value)
{
	if (!value)
		return (false);
	if (ft_strcmp(value, "echo\0") == 0 || ft_strcmp(value, "cd\0") == 0
		|| ft_strcmp(value, "pwd") == 0 || ft_strcmp(value, "export") == 0
		|| ft_strcmp(value, "unset") == 0 || ft_strcmp(value, "env") == 0
		|| ft_strcmp(value, "exit") == 0)
		return (true);
	return (false);
}

void	excute_command(char **cmd_array)
{
	if (is_builtin_cmd(cmd_array[0]))
		execute_builtin_cmd(cmd_array);
	else
		run_system_cmd(cmd_array);
}
