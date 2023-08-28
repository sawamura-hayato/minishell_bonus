/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:54:40 by tterao            #+#    #+#             */
/*   Updated: 2023/08/27 13:50:40 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include <stdlib.h>

void	exec_free_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	*exec_delete_file_free(char *file)
{
	unlink(file);
	free(file);
	return (NULL);
}
