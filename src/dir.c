#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// void	run_system_cmd(char **cmd, char **env)
// { ..
// 	pid_t	child_pid;

// 	child_pid = fork();
// 	if (child_pid < 0)
// 	{
// 		printf("%s", strerror(11));
// 		exit(11);
// 	}
// 	else if (child_pid == 0)
// 	{
// 		if (execve(cmd[0], cmd, env) < 0)
// 		{
// 			printf("minishell : %s : %s\n", strerror(errno), cmd[0]);
// 			exit(EXIT_SUCCESS);
// 		}
// 	}
// 	else
// 	{
// 		// if (bg) child in background
// 		// else
// 		wait(&child_pid);
// 	}
// }

/*int main(void)
{
    DIR             *dir;
    struct dirent   *entity;

    dir = opendir("/");
    entity = readdir(dir);
    while (entity)
    {
        printf("%d %s\n", entity->d_type, entity->d_name);
        entity = readdir(dir);
    }

    char path[10];

    if (getcwd(path, sizeof(path)) != NULL)
        printf("%s\n", path);
    else
        printf("%s", strerror(errno));
    closedir(dir);
    return (EXIT_SUCCESS);
}
*/
