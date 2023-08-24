/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:53:55 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/24 18:11:02 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parse.h"
#include "init.h"
#include "exec_command.h"

static int	dup_stdout_fd(t_ast *node, int *pipefd, t_data *d)
{
	int	fd;

	fd = -1;
	if (pipefd != NULL && node->command_list->fd == STDOUT_FILENO)
	{
		fd = dup(STDOUT_FILENO);
		try_close(pipefd[R], d);
		try_dup2(pipefd[W], STDOUT_FILENO, d);
		try_close(pipefd[W], d);
	}
	else if (node->command_list->fd != STDOUT_FILENO)
	{
		try_dup2(node->command_list->fd, STDOUT_FILENO, d);
		try_close(node->command_list->fd, d);
	}
	return (fd);
}

static void	reset_stdoutfd(int fd, t_data *d)
{
	try_dup2(fd, STDIN_FILENO, d);
	try_close(fd, d);
}

void	builtin(t_ast *node, int *pipefd, t_data *d)
{
	char		**argv;
	const int	dupped_stdoutfd = dup_stdout_fd(node, pipefd, d);

	argv = exec_make_argv(node);
	if (ft_strcmp_ignorecase(argv[0], "echo") == 0)
		builtin_echo(argv, d);
	else if (ft_strcmp_ignorecase(argv[0], "cd") == 0)
		builtin_cd(argv, d);
	else if (ft_strcmp_ignorecase(argv[0], "pwd") == 0)
		builtin_pwd(d);
	else if (ft_strcmp_ignorecase(argv[0], "export") == 0)
		builtin_export(argv, d);
	else if (ft_strcmp_ignorecase(argv[0], "unset") == 0)
		builtin_unset(argv, d);
	else if (ft_strcmp_ignorecase(argv[0], "env") == 0)
		builtin_env(argv, d);
	else if (ft_strcmp_ignorecase(argv[0], "exit") == 0)
		builtin_exit(argv, d);
	if (pipefd != NULL)
	{
		try_close(pipefd[W], d);
		exit(d->exit_status);
	}
	if (dupped_stdoutfd >= 0)
		reset_stdoutfd(dupped_stdoutfd, d);
}
