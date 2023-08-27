/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 00:22:15 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/27 22:11:47 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "init.h"
#include "library.h"
#define SIGNAL_EXITSTATUS 128

void	reset_vars(t_data *d)
{
	d->dupped_stdinfd = try_dup(STDIN_FILENO, d);
	d->syntax_flag = false;
}

void	end_command(char *line, t_data *d)
{
	free(line);
	try_dup2(d->dupped_stdinfd, STDIN_FILENO, d);
	try_close(d->dupped_stdinfd, d);
}

void	get_signal_num(t_data *d)
{
	if (signal_num != 0)
	{
		d->exit_status = SIGNAL_EXITSTATUS + signal_num;
		signal_num = 0;
		exit(signal_num);
	}
}
