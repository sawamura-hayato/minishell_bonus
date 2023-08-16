/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:06:35 by tterao            #+#    #+#             */
/*   Updated: 2023/08/16 20:01:12 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

bool	cd_iserror(char **argv);
void	cd_put_error_too_many_args(t_data *d);
bool	cd_is_cdpath(char *path);
void	cd_cdpath(char *path, t_data *d);

static void	cd_update(t_data *d)
{
	char	*cwd;
	char	*oldpwd;
	t_envs	*node;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror("getcwd"));
	free(d->oldpwd);
	d->oldpwd = d->pwd;
	d->pwd = cwd;
	node = envs_get_node("PWD", d->envs_hashmap);
	if (node != NULL)
		envs_modify("PWD", try_strdup(d->pwd), d->envs_hashmap);
	node = envs_get_node("OLDPWD", d->envs_hashmap);
	if (d->oldpwd != NULL)
		oldpwd = try_strdup(d->oldpwd);
	if (node != NULL)
		envs_modify("OLDPWD", oldpwd, d->envs_hashmap);
	else
		free(oldpwd);
}

static void	cd_nodir(t_data *d)
{
	t_envs		*node;
	const char	*msg = "cd: HOME not set\n";

	node = envs_get_node("HOME", d->envs_hashmap);
	if (node == NULL || node->value == NULL)
	{
		d->exit_status = EXIT_FAILURE;
		return (try_write(STDERR_FILENO, msg, ft_strlen(msg), d));
	}
	try_chdir(node->value, d);
	cd_update(d);
}

static void	cd_oldpwd(t_data *d)
{
	char	*msg;

	if (d->oldpwd == NULL)
	{
		msg = "cd: OLDPWD not set\n";
		return (try_write(STDERR_FILENO, msg, ft_strlen(msg), d));
	}
	if (!try_chdir(d->oldpwd, d))
		return ;
	msg = try_strjoin(d->oldpwd, "\n");
	try_write(STDOUT_FILENO, msg, ft_strlen(msg), d);
	free(msg);
	cd_update(d);
}

void	cd_exec(char *path, t_data *d)
{
	if (!try_chdir(path, d))
		return ;
	cd_update(d);
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
		return (cd_cdpath(argv[1], d));
	cd_exec(argv[1], d);
}
