/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:28:56 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/26 12:43:08 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SPACE ' '
#define NEWLINE '\n'
#define H_TAB '\t'
#define V_TAB '\v'
#define FORM_FEED '\f'
#define CARRAIGE_RETURN '\r'
#define TRUE (1)
#define FALSE (0)

int	ft_isspace(char c)
{
	if (c == SPACE || c == NEWLINE || c == H_TAB || c == V_TAB || \
			c == FORM_FEED || c == CARRAIGE_RETURN)
		return (TRUE);
	return (FALSE);
}

// #include <stdio.h>
// int main(void)
// {
// 	if (ft_isspace(' '))
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	if (ft_isspace('\n'))
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	if (ft_isspace('\v'))
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	if (ft_isspace('\t'))
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	if (ft_isspace('\r'))
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	if (ft_isspace('\f'))
// 		printf("ok\n");
// 	else
// 		printf("ko\n");
// 	if (ft_isspace('g'))
// 		printf("ko\n");
// 	else
// 		printf("ok\n");
// }
