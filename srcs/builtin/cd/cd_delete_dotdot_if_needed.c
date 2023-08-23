/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dotdot_if_needed.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:55:50 by tterao            #+#    #+#             */
/*   Updated: 2023/08/22 18:10:15 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DDC "/.."
#define D_SL "//"

char	*cd_delete_dotdot_if_needed(char *path, char *last_ddc)
{
	char	*newpath;
	char	*ddc;
	size_t	len;

	if (*path != '/')
		return (path);
	ddc = ft_strstr(last_ddc, DDC);
	if (ddc == NULL)
		return (path);
	len = ft_strlen(DDC);
	if (ddc == path || *(ddc + len) == '/')
		return (cd_delete_dotdot_if_needed(path, (ddc + len)));
	if (*(ddc + len) == '\0')
	{
		if (ft_strncmp(path, D_SL, ft_strlen(D_SL)) == 0)
			newpath = try_strdup("//");
		else
			newpath = try_strdup("/");
	}
	else
		newpath = try_strdup(ddc);
	free(path);
	return (cd_delete_dotdot_if_needed(newpath, newpath));
}
