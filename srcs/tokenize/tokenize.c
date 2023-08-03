/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:16 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/03 15:17:17 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "libft.h"
#include <stdlib.h>

t_token	*tokenize(const char *line)
{
	t_token	*head;
	// t_token	*token;
	t_quote	f_quote;
	size_t	index;
	char	*tmp_line;

	f_quote = DEFAULT;
	index = 0;
	head = create_token("WORD", WORD, index);
	tmp_line = (char *)line;
	while (*tmp_line != '\0')
	{
		if (token_can_get_quote_token(&head, &tmp_line, &f_quote, index))
			printf("OK\n") ;
		else
		{
			printf("KO\n") ;
			tmp_line++;		
		}
		// token = token_get_current_token(&tmp_line, f_quote);
		// token_addback(&head, token);
	}
	return (head);
}