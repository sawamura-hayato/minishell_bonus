/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_dup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/26 00:38:13 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "init.h"

void	try_dup2(int fildes, int fildes2, t_data *d)
{
	if (dup2(fildes, fildes2) == -1)
	{
		perror("dup");
		d->exit_status = EXIT_FAILURE;
		exit(d->exit_status);
	}
}
