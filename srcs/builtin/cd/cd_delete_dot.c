/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 17:55:14 by tterao            #+#    #+#             */
/*   Updated: 2023/08/18 14:58:22 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

#define CUR_DIR "./"
#define PRE_DIR "../"
#define DOT "."
#define DOTDOT ".."

void	cd_put_error_no_pwd(char *path, t_data *d);

static char	*delete_first_dot(const char *pwd, char *path)
{
	char	*new_path;

	if (ft_strlen(path) != ft_strlen(CUR_DIR))
		new_path = try_strjoin(pwd, "/");
	else
		new_path = try_strdup(pwd);
	new_path = try_strjoin_free(new_path, (path + ft_strlen(CUR_DIR)));
	free(path);
	return (new_path);
}

static char	*delete_first_dotdot(const char *pwd, char *path)
{
	char	*new_path;

	new_path = try_substr(pwd, 0, (ft_strrchr(pwd, '/') - pwd));
	if (ft_strlen(path) != ft_strlen(PRE_DIR))
		new_path = try_strjoin_free(new_path, "/");
	new_path = try_strjoin_free(new_path, (path + ft_strlen(PRE_DIR)));
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
		return (delete_first_dotdot(d->pwd, path));
	new_path = ft_strstr(path, CUR_DIR);
	if (new_path == path)
		return (delete_first_dot(d->pwd, path));
	new_path = ft_strstr(path, DOTDOT);
	if (new_path != NULL && *(new_path + ft_strlen(DOTDOT)) == '\0')
		return (delete_first_dotdot(d->pwd, try_strjoin_free(path, "/")));
	new_path = ft_strstr(path, DOT);
	if (new_path != NULL && *(new_path + ft_strlen(DOT)) == '\0')
		return (delete_first_dot(d->pwd, try_strjoin_free(path, "/")));
	return (path);
}
