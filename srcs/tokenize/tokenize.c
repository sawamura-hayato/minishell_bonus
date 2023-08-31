/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:16 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 11:04:58 by tterao           ###   ########.fr       */
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
		token_get_current_token(&head, &tmp_line);
	return (head);
}
