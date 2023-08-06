/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoperator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:52:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/26 16:58:04 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#define LOGICAL_OR '|'
#define LOGICAL_AND '&'

bool	ft_is_operator(char c)
{
	if (c == LOGICAL_OR || c == LOGICAL_AND)
		return (true);
	return (false);
}

// #include <stdio.h>
// int main(void)
// {
// 	if (ft_is_operator('l'))
// 		printf("ok\n");
// 	if (ft_is_operator('d'))
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	return (0);
// }