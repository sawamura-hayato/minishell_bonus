/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_overflow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:47:26 by tterao            #+#    #+#             */
/*   Updated: 2023/08/14 18:53:22 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static bool	isspace(char c)
{
	return (c == ' ' || c == '\t');
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

static void	overflow_long(const char *str, char sign)
{
	long long	num;

	num = 0;
	while (*str != '\0')
	{
		if (is_overflow(num, *str - '0', sign))
		{
			try_write("exit\nbash: exit: test: numeric argument required\n");
			exit(EXIT_NUMERIC_ARG);
		}
		num = num * 10 + (*str - '0');
		str++;
	}
}

void	overflow(char *str)
{
	char	sign;

	sign = '+';
	while (isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = *str;
		str++;
	}
	overflow_long(str, sign);
}
