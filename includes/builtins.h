/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:42:06 by tterao            #+#    #+#             */
/*   Updated: 2023/07/05 13:03:42 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	do_builtin(t_ast *node, int *pipefd, t_data *d);
void	builtin_echo(char **argv, t_data *d);
void	builtin_cd(char **argv, t_data *d);
void	builtin_pwd(char **argv, t_data *d);
void	builtin_export(char **argv, t_data *d);
void	builtin_unset(char **argv, t_data *d);
void	builtin_env(char **argv, t_data *d);
void	builtin_exit(char **argv, t_data *d);

void	do_builtin(t_ast *node, int *pipefd, t_data *d)
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
	else if ((ft_strcmp(argv[0], "cd") == 0)
		builtin_cd(argv, &d);
	else if ((ft_strcmp(argv[0], "pwd") == 0)
		builtin_pwd(argv, &d);
	else if ((ft_strcmp(argv[0], "export") == 0)
		builtin_export(argv, &d);
	else if ((ft_strcmp(argv[0], "unset") == 0)
		builtin_unset(argv, &d);
	else if ((ft_strcmp(argv[0], "env") == 0)
		builtin_env(argv, &d);
	else if ((ft_strcmp(argv[0], "exit") == 0)
		builtin_exit(argv, &d);
	if (pipefd != NULL)
	{
		try_close(pipefd[W]);
		exit(d->exit_status);
	}
}

#endif