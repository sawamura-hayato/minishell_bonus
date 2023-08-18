/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:38:47 by tterao            #+#    #+#             */
/*   Updated: 2023/08/18 18:40:27 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>
#define CUR_DIR "./"
#define PRE_DIR "../"
#define DOT "."
#define DOTDOT ".."

void	cd_exec(char *path, t_data *d);

#include <stdio.h>
bool	cd_is_cdpath(char *path)
{
	char	*dot_ptr;

	if (*path == '/')
		return (false);
	dot_ptr = ft_strstr(path, PRE_DIR);
	if (dot_ptr == path)
		return (false);
	dot_ptr = ft_strstr(path, CUR_DIR);
	if (dot_ptr == path)
		return (false);
	dot_ptr = ft_strstr(path, DOTDOT);
	if (dot_ptr == path && *(dot_ptr + ft_strlen(DOTDOT)) == '\0')
		return (false);
	dot_ptr = ft_strstr(path, DOT);
	if (dot_ptr == path && *(dot_ptr + ft_strlen(DOT)) == '\0')
		return (false);
	return (true);
}

char	*cd_join_pwd(char *path, t_data *d)
{
	char	*new_path;
	
	if (d->pwd == NULL)
	{
		cd_put_error_no_pwd(path, d);
		return (NULL);
	}
	new_path = try_strjoin(d->pwd, "/");
	new_path = try_strjoin_free(new_path, path);
	free(path);
	return (new_path);
}

void	cd_cdpath(char *path, t_data *d)
{
	char	*cdpath;

	cdpath = envs_get_value("CDPATH", d->envs_hashmap);
	printf("%s\n", cdpath);
	if (cdpath == NULL || *cdpath == '\0')
		return (cd_convert_path(cd_join_pwd(path, d), d));

}
