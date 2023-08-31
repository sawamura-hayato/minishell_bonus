/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:45:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 11:13:22 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_quote	token_set_flag_quote(char quote)
{
	if ('\'' == quote)
		return (SINGLE_QUOTE_FLAG);
	else if ('\"' == quote)
		return (DOUBLE_QUOTE_FLAG);
	return (DEFAULT);
}

t_token_type	token_set_flag_token(char *line)
{
	if (ft_strlen(line) > 2)
		return (WORD);
	else if ('(' == line[0])
		return (TK_OPEN_PARENTHESIS);
	else if (')' == line[0])
		return (TK_CLOSE_PARENTHESIS);
	else if ('|' == line[0])
	{
		if ('|' == line[1])
			return (TK_LOGICAL_OR);
		return (TK_PIPE);
	}
	else if ('&' == line[0] && '&' == line[1])
		return (TK_LOGICAL_AND);
	else if ('>' == line[0] || '<' == line[0])
		return (REDIRECT);
	return (WORD);
}
