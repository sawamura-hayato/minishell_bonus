/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/29 14:40:16 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "init.h"

int	try_open(int open_value, char *file, t_data *d)
{
	if (open_value < 0)
	{
		perror(file);
		d->exit_status = EXIT_FAILURE;
	}
	return (open_value);
}
