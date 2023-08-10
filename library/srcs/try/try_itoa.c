/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:51:02 by tterao            #+#    #+#             */
/*   Updated: 2023/08/10 16:10:19 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static	size_t	get_digit(long num)
{
	size_t	digit;

	digit = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		digit++;
	}
	while (num != 0)
	{
		num /= 10;
		digit++;
	}
	return (digit);
}

static void	make_str(char *str, long num, size_t digit)
{
	size_t	index;

	index = digit - 1;
	if (num == 0)
	{
		str[0] = '0';
		return ;
	}
	if (num < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	while (num != 0)
	{
		str[index] = (num % 10) + '0';
		num /= 10;
		index--;
	}
}

char	*try_itoa(int n)
{
	long	num;
	char	*str;
	size_t	digit;

	num = n;
	digit = get_digit(num);
	str = try_calloc(digit + 1, sizeof(char));
	make_str(str, num, digit);
	return (str);
}

// #include <stdio.h>
// int	main()
// {
// 	printf("%s\n", try_itoa(-0));
// 	printf("%s\n", try_itoa(-100));
// 	printf("%s\n", try_itoa(2424));
// }
