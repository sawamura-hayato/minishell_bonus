/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dotdot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:09:17 by tterao            #+#    #+#             */
/*   Updated: 2023/08/22 21:28:22 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DDC "/.."
#define D_SL "//"

char	*cd_delete_dotdot(char *path, char *last_ddc);

#include <stdio.h>
static bool	cd_is_file(char *path, char *dirpath)
{
	struct stat	sb;
	bool		is_file;

	if (stat(dirpath, &sb) == -1)
	{
		free(dirpath);
		return (false);
	}
	if (S_ISDIR(sb.st_mode) || S_ISLNK(sb.st_mode))
		is_file = false;
	else
	{
		is_file = true;
		free(path);
	}
	free(dirpath);
	return (is_file);
}

static char	*cd_delete_leading_comp(char *path, char *ddc)
{
	char			*newpath;
	const char		*following_ddc = ft_strstr(ddc + ft_strlen(DDC), DDC);
	const size_t	len = ft_strlen(DDC);

	printf("path=%s\n", path);
	printf("ddc=%s\n", ddc);
	printf("fddc=%s\n", following_ddc);
	if (following_ddc == NULL)
	{
		// printf("path=%s\n", path);
		if (ft_strncmp(path, D_SL, ft_strlen(D_SL)) == 0)
			newpath = try_strdup("//");
		else
			newpath = try_strdup("/");
		free(path);
		return (newpath);
	}
	if (ft_strncmp(path, DDC, ft_strlen(DDC)) == 0
		&& (*(path + len) == '/' || *(path + len) == '\0'))
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	newpath = try_strdup(ddc + len);
	// newpath = try_strdup(following_ddc);
	printf("new=%s\n", newpath);
	free(path);
	return (cd_delete_leading_comp(newpath, newpath));
}

static char	*cd_make_newpath(char *path, char *pre_comp, char *ddc)
{
	char		*newpath;
	const char	*l_dotdot = "/../";

	// printf("path=%s\n", path);
	// printf("ddc=%s\n", ddc);
	// printf("pre=%s\n", pre_comp);
	if (ft_strncmp(pre_comp, l_dotdot, ft_strlen(l_dotdot)) == 0)
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	newpath = try_substr(path, 0, pre_comp - path);
	// printf("newpath=%s\n", newpath);
	newpath = try_strjoin_free(newpath, (ddc + ft_strlen(DDC)));
	// printf("newpath=%s\n", newpath);
	free(path);
	return (cd_delete_dotdot(newpath, newpath));
}

char	*cd_delete_dotdot(char *path, char *last_ddc)
{
	char			*ddc;
	char			*pre_comp;
	const size_t	len = ft_strlen(DDC);

	ddc = ft_strstr(last_ddc, DDC);
	if (ddc == NULL)
		return (path);
	if (*(ddc + ft_strlen(ddc)) != '/' && *(ddc + ft_strlen(ddc)) != '\0')
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	if (cd_is_file(path, try_substr(path, 0, ddc - path)))
		return (NULL);
	pre_comp = ddc;
	printf("path=%s\n", path);
	printf("ddc=%s\n", pre_comp);
	if (ddc == path)
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	while (true)
	{
		if (pre_comp == path || (*pre_comp == '/' && (pre_comp - 1) == path))
			return (cd_delete_leading_comp(path, ddc));
		if (pre_comp != ddc && *pre_comp == '/' && *(pre_comp + 1) != '/')
			break ;
		pre_comp--;
	}
	printf("pre=%s\n\n", pre_comp);
	if (ft_strncmp(pre_comp, DDC, len) == 0 && *(pre_comp + len) != '/')
		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
	return (cd_make_newpath(path, pre_comp, ddc));
}
