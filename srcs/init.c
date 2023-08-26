/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 00:22:15 by tatyu             #+#    #+#             */
/*   Updated: 2023/08/26 00:39:39 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "init.h"
#include "library.h"

void	init(t_data *d)
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
