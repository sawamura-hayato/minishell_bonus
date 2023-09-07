/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_closedir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:06:31 by tterao            #+#    #+#             */
/*   Updated: 2023/09/05 16:09:59 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

void	try_closedir(DIR *dirp, t_data *d)
{
	if (closedir(dirp) == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("closedir");
	}
}
