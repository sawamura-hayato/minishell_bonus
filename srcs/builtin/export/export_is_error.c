/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_is_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:27:37 by tterao            #+#    #+#             */
/*   Updated: 2023/09/26 14:04:38 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "library.h"

void	export_invalid_identifier(char *str, t_data *d);

bool	export_is_symbol(char c)
{
	return (c == '~' || c == '`' || c == '!' || c == '@' || c == '#'
		|| c == '$' || c == '%' || c == '^' || c == '&' || c == '*'
		|| c == '(' || c == ')' || c == '-' || c == '=' || c == '+'
		|| c == '[' || c == '{' || c == ']' || c == '}' || c == '\\'
		|| c == '|' || c == ';' || c == ':' || c == '\'' || c == '\"'
		|| c == ',' || c == '<' || c == '.' || c == '>' || c == '?'
		|| c == '/' || c == '?');
}

static bool	export_is_invalid_key(char *str, t_data *d)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '+' || str[i] == '=')
	{
		export_invalid_identifier(str, d);
		return (true);
	}
	while (str[i] != '=' && str[i] != '+' && str[i] != '\0')
	{
		if (export_is_symbol(str[i]) || ft_isspace(str[i]))
		{
			export_invalid_identifier(str, d);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	export_is_invalid_operator(char *str, t_data *d)
{
	bool	plus_flag;

	plus_flag = false;
	while (*str != '\0')
	{
		if (!plus_flag && *str == '+')
		{
			str++;
			if (*str != '=')
			{
				export_invalid_identifier(str, d);
				return (true);
			}
			plus_flag = true;
			continue ;
		}
		str++;
	}
	return (false);
}

bool	export_is_error(char *str, t_data *d)
{
	if (export_is_invalid_key(str, d) || export_is_invalid_operator(str, d))
		return (true);
	return (false);
}
