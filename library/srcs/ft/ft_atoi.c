/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:14:03 by tterao            #+#    #+#             */
/*   Updated: 2023/08/10 17:46:22 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <limits.h>

#define UNSIGNED '+'
#define SIGNED '-'

static bool	is_space(char c)
{
	return (c == '\n' || c == '\t' || c == '\f'
		|| c == '\r' || c == '\v' || c == ' ');
}

static bool	iserror(const char *str)
{
	if (*str == '\0')
		return (true);
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (true);
		str++;
	}
	return (false);
}

static bool	is_overflow(long long sum, long long next_num, char sign)
{
	long long	of_div;
	long long	of_mod;

	if (sign == SIGNED)
	{
		of_div = LONG_MIN / (10 * -1);
		of_mod = LONG_MIN % (10 * -1);
	}
	else
	{
		of_div = LONG_MAX / 10;
		of_mod = LONG_MAX % 10;
	}
	if (sum > of_div || (sum == of_div && next_num > of_mod))
		return (true);
	return (false);
}

static int	make_num(const char *str, char sign)
{
	long long	num;

	num = 0;
	while (*str != '\0')
	{
		if (is_overflow(num, *str - '0', sign))
		{
			if (sign == SIGNED)
				return ((int)LONG_MIN);
			else
				return ((int)LONG_MAX);
		}
		num = num * 10 + (*str - '0');
		str++;
	}
	if (sign == '-')
		num *= -1;
	return (num);
}

int	ft_atoi(const char *str)
{
	char		sign;

	sign = '+';
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = *str;
		str++;
	}
	if (iserror(str))
		return (0);
	return (make_num(str, sign));
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main()
// {
// 	printf("%d\n", ft_atoi("2147483647"));
// 	printf("%d\n", ft_atoi("2147483648"));
// 	printf("ans %d\n", atoi("2147483648"));
// 	printf("%d\n", ft_atoi("-2147483648"));
// }
