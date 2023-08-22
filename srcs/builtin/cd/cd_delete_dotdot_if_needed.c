/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dotdot_if_needed.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:55:50 by tterao            #+#    #+#             */
/*   Updated: 2023/08/22 14:45:06 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DDC "/.."

#include <stdio.h>
char	*cd_delete_dotdot_if_needed(char *path, char *last_ddc)
{
	char	*newpath;
	char	*ddc;
	size_t	len;

	if (*path != '/')
		return (path);
	// printf("lastddc=%s\n", last_ddc);
	ddc = ft_strstr(last_ddc, DDC);
	// printf("ddc=%s\n", ddc);
	// printf("path=%s\n", path);
	if (ddc == NULL)
		return (path);
	len = ft_strlen(DDC);
	if (ddc == path || *(ddc + len) == '/')
		return (cd_delete_dotdot_if_needed(path, (ddc + len)));
	if (*(ddc + len) == '\0')
		newpath = try_strdup("/");
	else
		newpath = try_strdup(ddc);
	// printf("join=%s\n", ddc + len);
	// newpath = try_strjoin("/", ddc);
	// printf("new=%s\n", newpath);
	free(path);
	return (cd_delete_dotdot_if_needed(newpath, newpath));
}
