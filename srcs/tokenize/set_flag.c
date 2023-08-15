/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:45:59 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/15 15:49:18 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_quote token_set_flag_quote(char quote)
{
	if ('\'' == quote)
		return (SINGLE_QUOTE_FLAG);
	else if ('\"' == quote)
		return (DOUBLE_QUOTE_FLAG);
	return (DEFAULT);
}

t_token_type token_set_flag_token(char *line, t_quote f_quote)
{
	if (ft_strlen(line) > 2 || f_quote != DEFAULT)
		return (WORD);
	else if ('\'' == line[0])
		return (TOKEN_SINGLE_QUOTE);
	else if ('\"' == line[0])
		return (TOKEN_DOUBLE_QUOTE);
	else if ('|' == line[0])
	{
		if ('|' == line[1])
			return (TOKEN_LOGICAL_OR);
		return (TOKEN_PIPE);
	}
	else if ('&' == line[0] && '&' == line[1])
		return (TOKEN_LOGICAL_AND);
	else if ('>' == line[0] || '<' == line[0])
		return (REDIRECT);
	return (WORD);
}

// #include <stdio.h>
// int main()
// {
// 	char *str="||D";
// 	printf("OR   %d\n", token_set_flag_token(str));
// 	str="&&D";
// 	printf("AND   %d\n", token_set_flag_token(str));
// 	str="|D";
// 	printf("PIPE   %d\n", token_set_flag_token(str));
// 	str="\'D";
// 	printf("SING   %d\n", token_set_flag_token(str));
// 	str="\"d";
// 	printf("DOUB   %d\n", token_set_flag_token(str));
// 	str="d|D";
// 	printf("WORD   %d\n", token_set_flag_token(str));
// }