/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:18:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/07 22:58:33 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenize.h"

char	*token_get_current_word(char *line, size_t	size)
{
	size_t	i;
	char	*word;

	word = try_calloc(0, sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		word[i] = line[i];
		i++;
	}
	return (word);
}

void	token_get_current_token(t_token **head, \
								char **line, \
								t_quote f_quote, \
								size_t	*index)
{
	t_token			*current_token;
	size_t			size;
	char			*word;
	t_token_type	current_token_type;

	size = token_get_current_word_size(*line, f_quote);
	word = token_get_current_word(*line, size);
	current_token_type = token_set_flag_token(word, f_quote);
	current_token = create_token(word, current_token_type, *index);
	token_addback(head, current_token);
	*line += size;
}
