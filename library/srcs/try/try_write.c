/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:20:10 by tterao            #+#    #+#             */
/*   Updated: 2023/08/09 21:24:39 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>


void	try_write(int fildes, const void *buf, size_t nbyte)
{
	if (write(fildes, buf, nbyte) == -1)
		perror("write");
}
