/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:05:08 by tterao            #+#    #+#             */
/*   Updated: 2023/08/26 19:06:23 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cd_update(char *path, bool is_cdpath, t_data *d)
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

void	cd_exec(const char *og_path, char *path, bool is_cdpath, t_data *d)
{
	if (!try_chdir(og_path, path, d))
	{
		free(path);
		return ;
	}
	cd_update(path, is_cdpath, d);
}