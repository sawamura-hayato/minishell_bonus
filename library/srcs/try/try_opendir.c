/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_opendir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:49:33 by tterao            #+#    #+#             */
/*   Updated: 2023/09/03 20:18:52 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "library.h"

DIR	*try_opendir(const char *name, t_data *d)
{
	DIR	*dirp;

	dirp = opendir(name);
	if (dirp == NULL)
	{
		d->exit_status = EXIT_FAILURE;
		perror("opendir");
	}
	return (dirp);
}
