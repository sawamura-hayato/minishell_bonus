/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:06:35 by tterao            #+#    #+#             */
/*   Updated: 2023/08/26 19:26:22 by tterao           ###   ########.fr       */
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
void	cd_update(char *path, bool is_cdpath, t_data *d);
void	exec_free_argv(char **argv);

static char	**cd_nodir(char **argv, t_data *d)
{
	char		*path;
	char		**new_argv;
	const char	*msg = "cd: HOME not set\n";

	path = envs_get_value("HOME", d->envs_hashmap);
	if (path == NULL)
	{
		d->exit_status = EXIT_FAILURE;
		try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
		return (argv);
	}
	exec_free_argv(argv);
	new_argv = try_calloc(3, sizeof(char *));
	new_argv[0] = try_strdup("cd");
	new_argv[1] = path;
	return (builtin_cd(new_argv, d));
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

bool	cd_is_cdpath(char *path)
{
	return (
		*path != '/'
		&& ft_strncmp(path, DOT, ft_strlen(DOT) != 0)
		&& ft_strncmp(path, DOTDOT, ft_strlen(DOTDOT) != 0)
	);
}

char	**builtin_cd(char **argv, t_data *d)
{
	d->exit_status = EXIT_SUCCESS;
	if (cd_iserror(argv))
		cd_put_error_too_many_args(d);
	else if (argv[1] == NULL)
		return (cd_nodir(argv, d));
	else if (ft_strcmp(argv[1], "-") == 0)
		cd_oldpwd(d);
	else if (cd_is_cdpath(argv[1]))
		cd_cdpath(argv[1], try_strdup(argv[1]), d);
	else
		cd_convert_path_and_exec(argv[1], try_strdup(argv[1]), d, false);
	return (argv);
}
