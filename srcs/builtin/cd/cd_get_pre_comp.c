/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_pre_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:16:41 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/30 20:07:53 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>

char	*skip_r_consecutive_slashes(char *path, char *ddc)
{
	while (ddc != path)
	{
		if (*ddc != '/')
			break ;
		ddc--;
	}
	return (ddc);
}

static char	*skip_till_slash(char *path, char *pre_comp)
{
	while (pre_comp != path)
	{
		if (*pre_comp == '/')
			break ;
		pre_comp--;
	}
	return (pre_comp);
}

char	*get_precomp_start(char *path, char *pre_comp)
{
	while (pre_comp != path)
	{
		if (*(pre_comp - 1) != '/')
			break ;
		pre_comp--;
	}
	return (pre_comp);
}

char	*cd_get_pre_comp(char *path, char *ddc)
{
	char	*pre_comp;

	if (path == ddc)
		return (path);
	pre_comp = skip_r_consecutive_slashes(path, ddc);
	pre_comp = skip_till_slash(path, pre_comp);
	if (pre_comp == path)
		return (path);
	return (get_precomp_start(path, pre_comp));
}

bool	cd_is_slash_comp(char *pre_comp, char *ddc)
{
	while (pre_comp != ddc)
	{
		if (*pre_comp != '/')
			return (false);
		pre_comp++;
	}
	return (true);
}
