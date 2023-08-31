/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:20:10 by tterao            #+#    #+#             */
/*   Updated: 2023/08/31 12:39:02 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include "init.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

ssize_t	try_write(int fildes, const void *buf, size_t nbyte, t_data *d)
{
	const ssize_t	write_bytes = write(fildes, buf, nbyte);

	if (write_bytes == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("write");
	}
	return (write_bytes);
}
