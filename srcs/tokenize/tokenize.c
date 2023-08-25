/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:16 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/24 22:20:17 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdlib.h>
#include <stdio.h>

t_token	*tokenize(const char *line)
{
	t_token	*head;
	char	*tmp_line;

	head = NULL;
	tmp_line = (char *)line;
	while (*tmp_line != '\0')
	{

		token_get_current_token(&head, &tmp_line);
	}
	return (head);
}

// int main(void)
// {
// 	size_t size;

// 	size = token_get_current_word_size("echo");
// 	printf("size   %zu\n", size);
// 	return (0);
// }