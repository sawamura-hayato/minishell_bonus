/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_overflow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:47:26 by tterao            #+#    #+#             */
/*   Updated: 2023/08/15 16:21:07 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <limits.h>

void	exit_put_error_numeric(t_data *d, char *str);

#define UNSIGNED '+'
#define SIGNED '-'

bool	exit_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

static bool	is_overflow_long(long long sum, long long next_num, char sign)
{
	long long	of_div;
	long long	of_mod;

	if (sign == SIGNED)
	{
		of_div = LONG_MIN / -10;
		of_mod = LONG_MIN % -10;
		of_mod *= -1;
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

static bool	overflow_long(char *str, char sign)
{
	long long	num;

	num = 0;
	while (*str != '\0')
	{
		if (is_overflow_long(num, *str - '0', sign))
			return (true);
		num = num * 10 + (*str - '0');
		str++;
	}
	return (false);
}

bool	exit_is_overflow(char *str)
{
	char	sign;

	sign = '+';
	while (exit_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = *str;
		str++;
	}
	return (overflow_long(str, sign));
}
