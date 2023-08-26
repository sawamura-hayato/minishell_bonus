/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/26 00:40:19 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "init.h"

int	try_dup(int fildes, t_data *d)
{
	const int	fd = dup(fildes);
	if (fd == -1)
	{
		perror("dup");
		d->exit_status = EXIT_FAILURE;
		exit(d->exit_status);
	}
	return (fd);
}
