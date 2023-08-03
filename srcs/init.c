/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:06:19 by tterao            #+#    #+#             */
/*   Updated: 2023/08/03 18:20:57 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include <stdio.h>

void	envs_init(const char **environ, t_data d)
{
	while (*environ)
	{
		printf("%s\n", *environ);
		*environ++;
	}
}

int	main()
{
	t_data	d;

	extern char	**environ;
	envs_init(environ, d);
}
