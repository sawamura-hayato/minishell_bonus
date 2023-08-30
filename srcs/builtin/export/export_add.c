/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:08:49 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 18:58:47 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"
#include <stdlib.h>

bool	export_is_error(char *str, t_data *d);
void	export_set_oldpwd(const char *key, t_data *d);

typedef enum e_export_operator
{
	NEW,
	ADD,
}	t_export_operator;

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
	char	*op_ptr;
	size_t	len;

	if (op == NEW)
		c = '=';
	else
		c = '+';
	op_ptr = (char *)ft_memchr(str, c, ft_strlen(str));
	if (op_ptr == NULL)
		len = ft_strlen(str);
	else
		len = op_ptr - &str[0];
	return (try_substr(str, 0, len));
}

static char	*export_get_value(const char *str)
{
	char	*op_ptr;

	op_ptr = (char *)ft_memchr(str, '=', ft_strlen(str));
	if (op_ptr == NULL)
		return (NULL);
	return (try_strdup(op_ptr + 1));
}

static bool	is_underline(char *key)
{
	if (ft_strcmp(key, "_") == 0)
	{
		free(key);
		return (true);
	}
	return (false);
}

void	export_add(char *str, t_data *d)
{
	t_export_operator	op;
	char				*key;

	if (export_is_error(str, d))
		return ;
	op = export_get_operator(str);
	if (op == NEW)
	{
		key = export_get_key(str, op);
		if (is_underline(key))
			return ;
		envs_newnode(key, export_get_value(str),
			d->envs_hashmap);
	}
	else if (op == ADD)
	{
		key = export_get_key(str, op);
		if (is_underline(key))
			return ;
		envs_addstr(key, export_get_value(str),
			d->envs_hashmap);
	}
	export_set_oldpwd(export_get_key(str, op), d);
}
