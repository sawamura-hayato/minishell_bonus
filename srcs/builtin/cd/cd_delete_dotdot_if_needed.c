/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_delete_dotdot_if_needed.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:55:50 by tterao            #+#    #+#             */
/*   Updated: 2023/08/21 21:01:44 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>
#define DDC "/.."

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
	len = ft_strlen(ddc);
	if (*(ddc + len) != '/' || *(ddc + len) != '\0')
		return (cd_delete_dotdot_if_needed(path, (ddc + len)));
	if (*(ddc + len) == '/')
		len++;
	newpath = try_strjoin("/", (ddc + len));
	free(path);
	return (cd_delete_dotdot_if_needed(newpath, newpath));
}
