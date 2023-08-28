/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:35:31 by tterao            #+#    #+#             */
/*   Updated: 2023/08/28 14:21:25 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "init.h"
#define SIGNAL_EXITSTATUS 128

void	get_signal_num(t_data *d)
{
	if (signal_num != 0)
	{
		d->exit_status = SIGNAL_EXITSTATUS + signal_num;
		signal_num = 0;
	}
}

void	signal_put_error(const char *f, t_data *d)
{
	d->exit_status = EXIT_FAILURE;
	perror(f);
}
