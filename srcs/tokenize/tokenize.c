/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:16 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/04 15:54:39 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "library.h"
#include <stdlib.h>

t_token	*tokenize(const char *prompt)
{
	t_token	*head;
	// t_token	*token;
	t_quote	f_quote;
	size_t	index;

	f_quote = DEFAULT;
	index = 0;
	head = create_token("WORD", WORD, index);
	while (*prompt != '\0')
	{
		if (token_can_get_quote_token(&head, &prompt, &f_quote, index))
			printf("OK\n") ;
		else
		{
			printf("KO\n") ;
			prompt++;
		}
		// token = token_get_current_token(&prompt, f_quote);
		// token_addback(&head, token);
	}
	return (head);
}