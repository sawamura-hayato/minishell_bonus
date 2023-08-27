/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:22:01 by tterao            #+#    #+#             */
/*   Updated: 2023/08/27 23:09:55 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	handler(int signum)
{
	signal_num = signum;
	close(STDIN_FILENO);
}

static void	sigquit(t_data *d)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("sigemptyset");
		return ;
	}
	if (sigaddset(&act.sa_mask, SIGINT))
	{
		d->exit_status = EXIT_FAILURE;
		perror("sigaddset");
		return ;
	}
	if (sigaddset(&act.sa_mask, SIGQUIT))
	{
		d->exit_status = EXIT_FAILURE;
		perror("sigaddset");
		return ;
	}
	if (try_sigaction(SIGQUIT, &act, NULL, d) == -1)
		return ;
}

static void	sigint(t_data *d)
{
	struct sigaction	act;

	act.sa_handler = &handler;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) == -1)
	{
		d->exit_status = EXIT_FAILURE;
		perror("sigemptyset");
		return ;
	}
	if (sigaddset(&act.sa_mask, SIGINT))
	{
		d->exit_status = EXIT_FAILURE;
		perror("sigaddset");
		return ;
	}
	if (sigaddset(&act.sa_mask, SIGQUIT))
	{
		d->exit_status = EXIT_FAILURE;
		perror("sigaddset");
		return ;
	}
	if (try_sigaction(SIGQUIT, &act, NULL, d) == -1)
		return ;
}

void	set_signal_heredoc(t_data *d)
{
	sigint(d);
	sigquit(d);

}
