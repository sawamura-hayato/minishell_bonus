/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:56:59 by tterao            #+#    #+#             */
/*   Updated: 2023/08/23 20:00:36 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "library.h"

void	try_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
