/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_sigaction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:02:12 by tterao            #+#    #+#             */
/*   Updated: 2023/08/27 21:09:35 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include "library.h"

int	try_sigaction(int signum, const struct sigaction *act,
					struct sigaction *oldact, t_data *d)
{
	int	ret;

	ret = sigaction(signum, act, oldact);
	if (ret == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("sigaction");
	}
	return (ret);
}
