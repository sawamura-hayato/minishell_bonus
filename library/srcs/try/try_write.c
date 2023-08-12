/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:20:10 by tterao            #+#    #+#             */
/*   Updated: 2023/08/12 15:17:30 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include "init.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


void	try_write(int fildes, const void *buf, size_t nbyte, t_data *d)
{
	if (write(fildes, buf, nbyte) == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("write");
	}
}
