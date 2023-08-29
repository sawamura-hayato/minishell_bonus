/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:54:16 by tterao            #+#    #+#             */
/*   Updated: 2023/08/29 22:08:06 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "init.h"
#include <stdlib.h>

void	export_show(t_data *d);
bool	export_add(char *str, t_data *d);

void	builtin_export(char **argv, t_data *d)
{
	size_t	i;

	d->exit_status = EXIT_SUCCESS;
	if (argv[1] == NULL)
		return (export_show(d));
	i = 1;
	while (argv[i] != NULL)
	{
		if (export_add(argv[i], d) == false)
			return ;
		i++;
	}
}
