/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_waitpid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:36:05 by tterao            #+#    #+#             */
/*   Updated: 2023/08/26 16:17:57 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "library.h"

pid_t	try_waitpid(pid_t pid, int *wstatus, int options, t_data *d)
{
	pid_t	value;

	value = waitpid(pid, wstatus, options);
	if (value == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("waitpid");
	}
	return (value);
}
