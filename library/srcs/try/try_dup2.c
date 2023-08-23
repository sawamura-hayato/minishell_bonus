/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_dup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/23 15:18:52 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "init.h"

void	try_dup2(int fildes, int fildes2, t_data *d)
{
	if (dup2(fildes, fildes2) < 0)
	{
		perror("dup");
		d->exit_status = EXIT_FAILURE;
		exit(d->exit_status);
	}
}
