/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:06:35 by tterao            #+#    #+#             */
/*   Updated: 2023/08/25 22:15:04 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define CUR_DIR "./"
#define PRE_DIR "../"
#define DOT "."
#define DOTDOT ".."

bool	cd_iserror(char **argv);
void	cd_put_error_too_many_args(t_data *d);
bool	cd_is_cdpath(char *path);
void	cd_cdpath(const char *og_path, char *path, t_data *d);
char	*cd_delete_dot_firstcomp(char *path, t_data *d);
void	cd_convert_path_and_exec(const char *og_path, char *path,
			t_data *d, bool is_cdpath);

static void	cd_update(char *path, bool is_cdpath, t_data *d)
{
	t_envs	*node;
	char	*msg;

	free(d->oldpwd);
	d->oldpwd = d->pwd;
	d->pwd = path;
	node = envs_get_node("PWD", d->envs_hashmap);
	if (node != NULL)
		node->value = try_strdup(d->pwd);
	node = envs_get_node("OLDPWD", d->envs_hashmap);
	if (node != NULL && d->oldpwd != NULL)
		node->value = try_strdup(d->oldpwd);
	else if (node != NULL)
		node->value = NULL;
	if (is_cdpath == true)
	{
		msg = try_strjoin(path, "\n");
		try_write(STDOUT_FILENO, msg, ft_strlen(msg), d);
		free(msg);
	}
}

static void	cd_nodir(t_data *d)
{
	char		*path;
	const char	*msg = "cd: HOME not set\n";

	path = envs_get_value("HOME", d->envs_hashmap);
	if (path == NULL)
	{
		d->exit_status = EXIT_FAILURE;
		return (try_write(STDERR_FILENO, msg, ft_strlen(msg), d));
	}
	if (!try_chdir(path, path, d))
	{
		free(path);
		return ;
	}
	cd_update(path, false, d);
}

static void	cd_oldpwd(t_data *d)
{
	char	*msg;

	if (d->oldpwd == NULL)
	{
		msg = "cd: OLDPWD not set\n";
		return (try_write(STDERR_FILENO, msg, ft_strlen(msg), d));
	}
	if (!try_chdir(d->oldpwd, d->oldpwd, d))
		return ;
	cd_update(try_strdup(d->oldpwd), true, d);
}

void	cd_exec(const char *og_path, char *path, bool is_cdpath, t_data *d)
{
	if (!try_chdir(og_path, path, d))
	{
		free(path);
		return ;
	}
	cd_update(path, is_cdpath, d);
}

bool	cd_is_cdpath(char *path)
{
	return 
	(
		*path != '/'
		&& ft_strncmp(path, DOT, ft_strlen(DOT) != 0)
		&& ft_strncmp(path, DOTDOT, ft_strlen(DOTDOT) != 0)
	);
}

void	builtin_cd(char **argv, t_data *d)
{
	d->exit_status = EXIT_SUCCESS;
	if (cd_iserror(argv))
		return (cd_put_error_too_many_args(d));
	if (argv[1] == NULL)
		return (cd_nodir(d));
	if (ft_strcmp(argv[1], "-") == 0)
		return (cd_oldpwd(d));
	if (cd_is_cdpath(argv[1]))
		return (cd_cdpath(argv[1], try_strdup(argv[1]), d));
	cd_convert_path_and_exec(argv[1], try_strdup(argv[1]), d, false);
}
