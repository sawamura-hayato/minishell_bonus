/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:47:34 by tterao            #+#    #+#             */
/*   Updated: 2023/08/16 17:26:47 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

void	builtin_unset(char **argv, t_data *d)
{
	size_t	i;

	d->exit_status = EXIT_SUCCESS;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strcmp(argv[i], "_") != 0)
			envs_delete(argv[i], d->envs_hashmap);
		if (ft_strcmp(argv[i], "OLDPWD") == 0)
		{
			free(d->oldpwd);
			d->oldpwd = NULL;
		}
		i++;
	}
}
