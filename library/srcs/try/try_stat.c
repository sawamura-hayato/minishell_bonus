/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:29:30 by tterao            #+#    #+#             */
/*   Updated: 2023/08/19 18:28:55 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

bool	try_stat(const char *path, struct stat *sb, t_data *d)
{
	if (stat(path, sb) == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("stat");
		return (false);
	}
	return (true);
}
