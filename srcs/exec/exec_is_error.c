/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_is_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:11:54 by tterao            #+#    #+#             */
/*   Updated: 2023/08/25 11:12:59 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include "library.h"
#define CURDIR "./"
#define PREDIR "../"
#define DOTDOT ".."
#define AB_PATH "/"

void	exec_put_error_is_dir(const char *command, t_data *d);
void	exec_put_error_cmd_not_found(const char *command, t_data *d);
void	exec_put_error_no_file(const char *command, t_data *d);
void	exec_put_error_no_permission(const char *command, t_data *d);

static bool	is_path(const char *command)
{
	return (
		ft_strncmp(command, CURDIR, ft_strlen(CURDIR)) == 0
		|| ft_strncmp(command, PREDIR, ft_strlen(PREDIR)) == 0
		|| (ft_strncmp(command, DOTDOT, ft_strlen(DOTDOT)) == 0
			&& *(command + ft_strlen(DOTDOT)) == '\0')
		|| *command == '/'
	);
}

static bool	is_dir(const char *dirpath)
{
	struct stat	sb;

	if (stat(dirpath, &sb) == -1)
		return (false);
	if (S_ISDIR(sb.st_mode))
		return (true);
	if (S_ISLNK(sb.st_mode))
		return (true);
	return (false);
}

static bool	is_file(const char *path)
{
	return (access(path, F_OK) == 0);
}

void	exec_is_error(const char *argv, const char *filepath, t_data *d)
{
	if (is_path(argv) && is_dir(argv))
		exec_put_error_is_dir(argv, d);
	if (is_path(argv) && is_file(argv) && access(argv, X_OK) != 0)
		exec_put_error_no_permission(argv, d);
	if (envs_get_node("PATH", d->envs_hashmap) == NULL
		&& !is_path(argv) && filepath == NULL)
		exec_put_error_no_file(argv, d);
}
