/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:40:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/23 15:19:15 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "init.h"

// try_open(open(), d)
// 可変長配列実装するのがめんどくさいので、openした値を見て判断する

int	try_open(int open_value, t_data *d)
{
	if(open_value < 0)
	{
		perror("open");
		d->exit_status = EXIT_FAILURE;
		exit(d->exit_status);
	}
	return (open_value);
}


// RETURN VALUES
//      If successful, open() returns a non-negative integer, termed a file descriptor.  It returns -1 on failure, and sets errno to
//      indicate the error.
