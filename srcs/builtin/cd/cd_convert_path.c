/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_convert_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:29:32 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/20 14:36:11 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

void	cd_put_error_no_pwd(char *path, t_data *d);

#include <stdio.h>
static char	*cd_join_pwd(char *path, t_data *d)
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

void	cd_convert_path(char *path, t_data *d, bool is_cdpath)
{
	if (path == NULL)
		return ;
	printf("%s\n", path);
}
