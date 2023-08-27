/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:57:21 by tterao            #+#    #+#             */
/*   Updated: 2023/08/27 18:05:10 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include "init.h"
#include <stdlib.h>

void	end_command(char *line, t_data *d);

void	eof(t_data *d)
{
	const char	*msg = "exit\n";

	end_command(NULL, d);
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	exit(d->exit_status);
}
