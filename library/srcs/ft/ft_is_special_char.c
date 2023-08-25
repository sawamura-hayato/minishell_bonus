/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:54:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/24 21:55:52 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#define LOGICAL_OR '|'
#define LOGICAL_AND '&'
#define	REDIRECTING_INPUT '<'
#define	REDIRECTING_OUTPUT '>'
#define	OPEN_PARENTHESIS '('
#define	CLOSE_PARENTHESIS ')'

bool	ft_is_special_char(char c)
{
	if (c == LOGICAL_OR || c == LOGICAL_AND || \
			c == REDIRECTING_INPUT || c == REDIRECTING_OUTPUT || \
			c == OPEN_PARENTHESIS || c == CLOSE_PARENTHESIS)
		return (true);
	return (false);
}