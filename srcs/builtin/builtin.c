/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:53:55 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/08 18:55:32 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "parse.h"
#include "init.h"

void	builtin(t_ast *node, int *pipefd, t_data *d)
{
	if (pipefd != NULL && node->command_list->fd == STDOUT_FILENO)
	{
		try_close(pipefd[R]);
		try_dup2(pipefd[W], STDOUT_FILENO);
		try_close(STDOUT_FILENO);
	}
	else if (node->command_list->fd != STDOUT_FILENO)
	{
		try_dup2(node->command_list->fd, STDOUT_FILENO);
		try_close(STDOUT_FILENO);
	}
	char	**argv = exec_make_command_array(node);
	if (ft_strcmp(argv[0], "echo") == 0)
		builtin_echo(argv, &d);
	else if (ft_strcmp(argv[0], "cd") == 0)
		builtin_cd(argv, &d);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		builtin_pwd(argv, &d);
	else if (ft_strcmp(argv[0], "export") == 0)
		builtin_export(argv, &d);
	else if (ft_strcmp(argv[0], "unset") == 0)
		builtin_unset(argv, &d);
	else if (ft_strcmp(argv[0], "env") == 0)
		builtin_env(argv, &d);
	else if (ft_strcmp(argv[0], "exit") == 0)
		builtin_exit(argv, &d);
	if (pipefd != NULL)
	{
		try_close(pipefd[W]);
		exit(d->exit_status);
	}
}
