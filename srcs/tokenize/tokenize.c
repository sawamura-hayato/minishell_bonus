/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:16 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/05 19:07:03 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdlib.h>

t_token	*tokenize(const char *line)
{
	t_token	*head;
	t_quote	f_quote;
	size_t	index;
	char	*tmp_line;

	f_quote = DEFAULT;
	index = 0;
	head = NULL;
	tmp_line = (char *)line;
	while (*tmp_line != '\0')
	{
		index = token_can_get_next_token_index(head, &tmp_line, f_quote, index);
		if (!token_can_get_quote_token(&head, &tmp_line, &f_quote, index))
			token_get_current_token(&head, &tmp_line, f_quote, &index);
	}
	return (head);
}
