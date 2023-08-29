/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:05:08 by tterao            #+#    #+#             */
/*   Updated: 2023/08/29 22:34:02 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	updata_env_var(const char *key, const char *value, t_data *d)
{
	t_envs	*node;

	node = envs_get_node(key, d->envs_hashmap);
	if (node == NULL)
		return ;
	free(node->value);
	if (value != NULL)
		node->value = try_strdup(value);
	else
		node->value = NULL;
}

void	cd_update(char *path, bool is_cdpath, t_data *d)
{
	char	*msg;

	free(d->oldpwd);
	d->oldpwd = d->pwd;
	d->pwd = path;
	updata_env_var("PWD", d->pwd, d);
	updata_env_var("OLDPWD", d->pwd, d);
	if (is_cdpath == true)
	{
		msg = try_strjoin(path, "\n");
		try_write(STDOUT_FILENO, msg, ft_strlen(msg), d);
		free(msg);
	}
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
