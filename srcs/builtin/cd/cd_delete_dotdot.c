/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dotdot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:09:17 by tterao            #+#    #+#             */
/*   Updated: 2023/08/25 18:59:00 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DDC "/.."
#define DDCS "/../"
#define DDDC "//.."
#define DDDCS "//../"
#define D_SL "//"

char	*cd_delete_dotdot(char *path, char *last_ddc);
char	*cd_get_pre_comp(char *path, char *ddc);
bool	cd_is_slash_comp(char *pre_comp, char *ddc);

#include <stdio.h>
bool	is_dotdotcomp(char *path)
{
	return (
		(ft_strncmp(path, DDC, ft_strlen(DDC)) == 0 && *(path + ft_strlen(DDC)) == '\0')
		|| ft_strncmp(path, DDCS, ft_strlen(DDCS)) == 0
		|| (ft_strncmp(path, DDDC, ft_strlen(DDDC)) == 0 && *(path + ft_strlen(DDDC)) == '\0')
		|| ft_strncmp(path, DDDCS, ft_strlen(DDDCS)) == 0
	);
}

static bool	cd_is_file(char *path, char *dirpath)
{
	struct stat	sb;
	bool		is_file;

	if (stat(dirpath, &sb) == -1)
	{
		free(dirpath);
		return (false);
	}
	if (S_ISREG(sb.st_mode))
	{
		is_file = true;
		free(path);
	}
	else
		is_file = false;
	free(dirpath);
	return (is_file);
}

// static char	*cd_delete_leading_comp(char *path, char *ddc)
// {
// 	char			*newpath;
// 	const char		*following_ddc = ft_strstr(ddc + ft_strlen(DDC), DDC);
// 	const size_t	len = ft_strlen(DDC);

// 	printf("path=%s\n", path);
// 	printf("ddc=%s\n", ddc);
// 	printf("fddc=%s\n", following_ddc);
// 	if (following_ddc == NULL)
// 	{
// 		// printf("path=%s\n", path);
// 		newpath = ft_substr(path, 0, ddc - path);
// 		if (cd_is_file(path, newpath))
// 			return (NULL);
// 		free(newpath);
// 		if (ft_strncmp(path, D_SL, ft_strlen(D_SL)) == 0)
// 			newpath = try_strdup("//");
// 		else
// 			newpath = try_strdup("/");
// 		free(path);
// 		return (newpath);
// 	}
// 	if (is_dotdotcomp(path))
// 		return (cd_delete_dotdot(path, (ddc + ft_strlen(DDC))));
// 	newpath = try_strdup(ddc + len);
// 	// newpath = try_strdup(following_ddc);
// 	printf("new=%s\n", newpath);
// 	free(path);
// 	return (cd_delete_leading_comp(newpath, newpath));
// }

char	*skip_consecutive_slashes(char *path)
{
	while (*path != '\0')
	{
		if (*path != '/')
			break ;
		path++;
	}
	return (path);
}

static char	*cd_make_newpath(char *path, char *pre_comp, char *ddc)
{
	char		*newpath;

	// printf("path=%s\n", path);
	// printf("ddc=%s\n", ddc);
	// printf("pre=%s\n", pre_comp);
	if (cd_is_slash_comp(pre_comp, ddc))
		return (cd_delete_dotdot(path, (ddc + ft_strlen(ddc))));
	if (cd_is_file(path, try_substr(path, 0, ddc - path)))
		return (NULL);
	if (pre_comp != path)
	{
		newpath = try_substr(path, 0, pre_comp - path);
		newpath = try_strjoin_free(newpath, (ddc + ft_strlen(DDC)));
	}
	else
	{
		newpath = try_substr(path, 0, skip_consecutive_slashes(path) - path);
		newpath = try_strjoin_free(newpath, (ddc + ft_strlen(DDC) + 1));
	}
	// printf("newpath=%s\n", newpath);
	// printf("front=%s\n", newpath);
	free(path);
	return (cd_delete_dotdot(newpath, newpath));
}


//../../../..test/../////test../
//..test/../../..test/../////test../
///////../////../../..test/../////test../
char	*cd_delete_dotdot(char *path, char *last_ddc)
{
	char			*ddc;
	char			*pre_comp;
	const size_t	ddc_len = ft_strlen(DDC);

	ddc = ft_strstr(last_ddc, DDC);
	if (ddc == NULL)
		return (path);
	if (!is_dotdotcomp(ddc) || ddc == path)
		return (cd_delete_dotdot(path, ddc + ddc_len));
	if (cd_is_file(path, try_substr(path, 0, ddc - path)))
		return (NULL);
	pre_comp = cd_get_pre_comp(path, ddc);
	if (is_dotdotcomp(pre_comp))
		return (cd_delete_dotdot(path, (ddc + ddc_len)));
	return (cd_make_newpath(path, pre_comp, ddc));
}
