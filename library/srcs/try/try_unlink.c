/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_unlink.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:41:32 by tterao            #+#    #+#             */
/*   Updated: 2023/08/27 13:43:49 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void	try_unlink(const char *pathname, t_data *d)
{
	if (unlink(pathname) == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("unlink");
	}
}
