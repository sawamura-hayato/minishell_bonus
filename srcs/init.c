/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 00:22:15 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/29 23:56:25 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "init.h"
#include "library.h"
#define SIGQUIT_EXITSTATUS 131

void	put_sigquit_line(t_data *d);

void	reset_vars(t_data *d)
{
	d->dupped_stdinfd = try_dup(STDIN_FILENO, d);
	d->syntax_flag = false;
	d->sigint_flag = false;
	g_signal_num = 0;
}

void	end_command(char *line, t_data *d)
{
	if (d->sigint_flag)
		try_write(STDERR_FILENO, "\n", 1, d);
	if (d->exit_status == SIGQUIT_EXITSTATUS)
		put_sigquit_line(d);
	free(line);
	try_dup2(d->dupped_stdinfd, STDIN_FILENO, d);
	try_close(d->dupped_stdinfd, d);
}
