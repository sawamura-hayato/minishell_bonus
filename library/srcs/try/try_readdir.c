/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_readdir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:55:31 by tterao            #+#    #+#             */
/*   Updated: 2023/09/03 20:16:01 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "library.h"

struct dirent	*try_readdir(DIR *dirp, t_data *d)
{
	struct dirent	*entry;

	errno = 0;
	entry = readdir(dirp);
	if (entry == NULL && errno != 0)
	{
		d->exit_status = EXIT_FAILURE;
		perror("readdir");
	}
	return (entry);
}
