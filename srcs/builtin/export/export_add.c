/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:08:49 by tterao            #+#    #+#             */
/*   Updated: 2023/08/12 19:23:21 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>

bool	export_is_error(char *str, t_data *d);

typedef enum e_export_operator
{
	NEW,
	ADD,
}t_export_operator;

static t_export_operator	export_get_operator(char *str)
{
	while (*str != '\0')
	{
		if (*str == '=')
			return (NEW);
		else if (*str == '+')
			return (ADD);
		str++;
	}
	return (NEW);
}

static char	*export_get_key(const char *str, t_export_operator op)
{
	char	c;

	if (op == NEW)
		c = '=';
	else
		c = '+';
	return (
		try_substr(
			str,
			0,
			(char *)ft_memchr(str, c, ft_strlen(str)) - &str[0]
		));
}

static char	*export_get_value(const char *str)
{
	char	*op_ptr;

	op_ptr = (char *)ft_memchr(str, '=', ft_strlen(str));
	if (op_ptr == NULL)
		return (NULL);
	return (try_strdup(op_ptr + 1));
}


bool	export_add(char *str, t_data *d)
{
	t_export_operator	op;

	if (export_is_error(str, d))
		return (false);
	op = export_get_operator(str);
	if (op == NEW)
		envs_newnode(export_get_key(str, op), export_get_value(str),
			d->envs_hashmap);
	else if (op == ADD)
		envs_addstr(export_get_key(str, op), export_get_value(str),
			d->envs_hashmap);
	return (true);
}
