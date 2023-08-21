/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dotdot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:09:17 by tterao            #+#    #+#             */
/*   Updated: 2023/08/21 17:06:18 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DDC "/.."

char	*cd_delete_dotdot(char *path, char *last_ddc);

#include <stdio.h>
static char	*cd_delete_leading_comp(char *path, char *ddc)
{
	char		*newpath;
	const char	*following_ddc = ft_strstr(ddc + ft_strlen(DDC), DDC);

	printf("folling=%s\n", following_ddc);
	if (following_ddc == NULL)
	{
		free(path);
		return (try_strdup("/"));
	}
	if (ft_strncmp(path, DDC, ft_strlen(DDC)) == 0)
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	newpath = try_strdup(following_ddc);
	free(path);
	return (newpath);
}

char	*cd_delete_dotdot(char *path, char *last_ddc)
{
	char	*newpath;
	char	*ddc;
	char	*pre_comp;

	ddc = ft_strstr(last_ddc, DDC);
	printf("ddc=%s\n", ddc);
	printf("path=%s\n", path);
	if (ddc == NULL)
		return (path);
	if (*(ddc + ft_strlen(ddc)) != '/' && *(ddc + ft_strlen(ddc)) != '\0')
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	pre_comp = ddc;
	if (ddc == path)
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	while (true)
	{
		if (pre_comp == path)
			return (cd_delete_leading_comp(path, ddc));
		if (pre_comp != ddc && *pre_comp == '/' && *(pre_comp + 1) != '/')
			break ;
		pre_comp--;
	}
	printf("pre=%s\n", pre_comp);
	if (ft_strncmp(pre_comp, DDC, ft_strlen(DDC)) == 0)
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	newpath = try_substr(path, 0, pre_comp - path);
	newpath = try_strjoin_free(newpath, (ddc + ft_strlen(DDC)));
	free(path);
	printf("newpath=%s\n\n", newpath);
	return (cd_delete_dotdot(newpath, newpath));
}
