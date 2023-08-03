/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_meta_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:54:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/03 17:57:23 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#define LOGICAL_OR '|'
#define LOGICAL_AND '&'
#define	REDIRECTING_INPUT '<'
#define	REDIRECTING_OUTPUT '>'

bool	ft_is_meta_char(char c)
{
	if (c == LOGICAL_OR || c == LOGICAL_AND || \
			c == REDIRECTING_INPUT || c == REDIRECTING_INPUT )
		return (true);
	return (false);
}