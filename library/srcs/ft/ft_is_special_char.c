/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:54:08 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 11:13:06 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#define LOGICAL_OR '|'
#define LOGICAL_AND '&'
#define REDIRECTING_INPUT '<'
#define REDIRECTING_OUTPUT '>'
#define OPEN_PARENTHESIS '('
#define CLOSE_PARENTHESIS ')'

bool	ft_is_special_char(char c)
{
	if (c == LOGICAL_OR || c == LOGICAL_AND || \
			c == REDIRECTING_INPUT || c == REDIRECTING_OUTPUT || \
			c == OPEN_PARENTHESIS || c == CLOSE_PARENTHESIS)
		return (true);
	return (false);
}
