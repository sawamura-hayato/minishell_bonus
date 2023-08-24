/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:45 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/23 15:18:47 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "init.h"

void	try_dup(int fildes, t_data *d)
{
	if (dup(fildes) < 0)
	{
		perror("dup");
		d->exit_status = EXIT_FAILURE;
		exit(d->exit_status);
	}
}
