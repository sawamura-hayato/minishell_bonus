/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_strjoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:51:21 by tterao            #+#    #+#             */
/*   Updated: 2023/08/12 15:51:58 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdlib.h>

char	*try_strjoin_free(char *free_str, const char *str2)
{
	char	*new_str;

	new_str = try_strjoin(free_str, str2);
	free(free_str);
	return (new_str);
}
