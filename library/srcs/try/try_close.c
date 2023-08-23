/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:48 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/23 15:19:01 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "init.h"

void	try_close(int fildes, t_data *d)
{
	if (close(fildes) < 0)
	{
		perror("close");
		d->exit_status = EXIT_FAILURE;
		exit(d->exit_status);
	}
}
