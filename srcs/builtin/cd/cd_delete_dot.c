/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:55:14 by tterao            #+#    #+#             */
/*   Updated: 2023/08/17 18:50:44 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

#define CUR_DIR "./"
#define PRE_DIR "../"

void	cd_put_error_no_pwd(char *path, t_data *d);

static char	*delete_first_dot(const char *pwd, char *path, size_t len)
{
	char	*new_path;

	new_path = try_strjoin(pwd, "/");
	new_path = try_strjoin_free(new_path, (path + len));
	free(path);
	return (new_path);
}

char	*cd_delete_dot_firstcomp(char *path, t_data *d)
{
	char	*new_path;

	if (d->pwd == NULL)
	{
		cd_put_error_no_pwd(path, d);
		return (NULL);
	}
	new_path = ft_strstr(path, PRE_DIR);
	if (new_path == path)
		return (delete_first_dot(d->pwd, path, ft_strlen(PRE_DIR)));
	new_path = ft_strstr(path, CUR_DIR);
	if (new_path == path)
		return (delete_first_dot(d->pwd, path, ft_strlen(CUR_DIR)));
	return (path);
}
