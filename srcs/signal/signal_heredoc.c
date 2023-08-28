/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:22:01 by tterao            #+#    #+#             */
/*   Updated: 2023/08/28 17:34:57 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	signal_put_error(const char *f, t_data *d);

static void	handler(int signum)
{
	g_signal_num = signum;
	close(STDIN_FILENO);
}

static void	sigquit(t_data *d)
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) == -1)
		return (signal_put_error("sigemptyset", d));
	if (sigaddset(&act.sa_mask, SIGINT) == -1)
		return (signal_put_error("sigaddset", d));
	if (sigaddset(&act.sa_mask, SIGQUIT) == -1)
		return (signal_put_error("sigaddset", d));
	if (try_sigaction(SIGQUIT, &act, NULL, d) == -1)
		return ;
}

static void	sigint(t_data *d)
{
	struct sigaction	act;

	act.sa_handler = &handler;
	act.sa_flags = 0;
	if (sigemptyset(&act.sa_mask) == -1)
		return (signal_put_error("sigemptyset", d));
	if (sigaddset(&act.sa_mask, SIGINT) == -1)
		return (signal_put_error("sigaddset", d));
	if (sigaddset(&act.sa_mask, SIGQUIT) == -1)
		return (signal_put_error("sigaddset", d));
	if (try_sigaction(SIGINT, &act, NULL, d) == -1)
		return ;
}

void	set_signal_heredoc(t_data *d)
{
	sigint(d);
	sigquit(d);
}
