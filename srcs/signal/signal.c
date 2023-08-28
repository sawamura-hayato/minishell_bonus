/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:35:31 by tterao            #+#    #+#             */
/*   Updated: 2023/08/28 17:42:19 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "init.h"
#include "library.h"
#define SIGNAL_EXITSTATUS 128

void	get_signal_num(t_data *d)
{
	if (g_signal_num != 0)
	{
		d->exit_status = SIGNAL_EXITSTATUS + g_signal_num;
		g_signal_num = 0;
	}
}

void	signal_put_error(const char *f, t_data *d)
{
	d->exit_status = EXIT_FAILURE;
	perror(f);
}

void	ignore_signal(t_data *d)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) == -1)
		return (signal_put_error("sigemptyset", d));
	if (sigaddset(&act.sa_mask, SIGINT))
		return (signal_put_error("sigaddset", d));
	if (sigaddset(&act.sa_mask, SIGQUIT))
		return (signal_put_error("sigaddset", d));
	if (try_sigaction(SIGINT, &act, NULL, d) == -1)
		return ;
	if (try_sigaction(SIGQUIT, &act, NULL, d) == -1)
		return ;
}
