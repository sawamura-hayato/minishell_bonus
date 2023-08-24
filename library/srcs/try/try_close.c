/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:48 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/24 14:28:59 by tterao           ###   ########.fr       */
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
	}
}
