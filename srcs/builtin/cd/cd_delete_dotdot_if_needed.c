/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dotdot_if_needed.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:55:50 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 19:36:41 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DDC "/.."

bool	is_dotdotcomp(char *path);
char	*skip_consecutive_slashes(char *path);

static char	*get_end_comp(char *ddc)
{
	ddc += ft_strlen(DDC);
	if (*ddc == '/')
		ddc++;
	return (ddc);
}

char	*cd_delete_dotdot_if_needed(char *path, char *last_ddc)
{
	char			*newpath;
	char			*ddc;
	const size_t	ddc_len = ft_strlen(DDC);

	if (*path != '/')
		return (path);
	ddc = ft_strstr(last_ddc, DDC);
	if (ddc == NULL)
		return (path);
	if (!is_dotdotcomp(ddc))
		return (cd_delete_dotdot_if_needed(path, (ddc + ddc_len)));
	if ((ddc + 1) == skip_consecutive_slashes(path))
		newpath = try_substr(path, 0, skip_consecutive_slashes(path) - path);
	else
		newpath = try_substr(path, 0, (ddc - path));
	newpath = try_strjoin_free(newpath, get_end_comp(ddc));
	free(path);
	return (cd_delete_dotdot_if_needed(newpath, newpath));
}
