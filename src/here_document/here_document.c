/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:46:07 by msales-a          #+#    #+#             */
/*   Updated: 2021/10/16 20:35:01 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_sigint(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit(2);
}

static void	doc_writer(int fd, char *value)
{
	char	*line;

	signal(SIGINT, handler_sigint);
	while (true)
	{
		if (g_minishell.interactive)
			ft_putstr_fd("> ", STDOUT_FILENO);
		if (get_next_line(STDIN_FILENO, &line) <= 0)
		{
			error_heredoc_eof(value);
			if (g_minishell.interactive)
				exit(1);
			break ;
		}
		//g_minishell.general_line++;
		if (!line || ft_strcmp(value, line) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	if (g_minishell.interactive)
		exit(0);
}

static char	*doc_reader(int fd)
{
	char			*line;
	t_str_builder	*builder;

	builder = str_builder_init();
	while (get_next_line(fd, &line) > 0)
	{
		g_minishell.heredoc_line++;
		str_builder_add_str(builder, line);
		str_builder_add_char(builder, '\n');
		free(line);
		line = NULL;
	}
	if (line)
	{
		free(line);
		g_minishell.heredoc_line++;
	}
	line = ft_strdup(builder->str);
	str_builder_destroy(builder);
	return (line);
}

char	*heredoc(char *value)
{
	int		fd[2];
	pid_t	pid;
	int		exit_code;
	char	*line;

	if (pipe(fd) == -1)
		return (NULL);
	pid = 0;
	if (g_minishell.interactive)
		pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		doc_writer(fd[1], value);
	close(fd[1]);
	waitpid(pid, &exit_code, 0);
	line = doc_reader(fd[0]);
	close(fd[0]);
	if (WIFEXITED(exit_code) && WEXITSTATUS(exit_code) > 1)
	{
		g_minishell.error_status = 130;
		free(line);
		return (NULL);
	}
	g_minishell.error_status = 0;
	return (line);
}
