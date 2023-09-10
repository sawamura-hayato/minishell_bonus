/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 00:22:15 by tatyu             #+#    #+#             */
/*   Updated: 2023/09/09 17:59:59 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "init.h"
#include "library.h"

void	reset_vars(t_data *d)
{
	d->dupped_stdinfd = try_dup(STDIN_FILENO, d);
	d->syntax_flag = false;
	g_signal_num = 0;
}

void	end_command(char *line, t_data *d)
{
	free(line);
	try_dup2(d->dupped_stdinfd, STDIN_FILENO, d);
	try_close(d->dupped_stdinfd, d);
}
