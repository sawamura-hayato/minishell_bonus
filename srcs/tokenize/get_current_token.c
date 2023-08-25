/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:18:29 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/24 22:19:55 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenize.h"

static char	token_set_type_word(char c)
{
	if (c == '\'')
		return (IS_SINGLE_QUOTED + '0');
	else if  (c == '\"')
		return (IS_DOUBLE_QUOTED + '0');
	return (DEFAULT_CHAR_TYPE + '0');
}

char	*token_get_current_word(char *line, size_t	size)
{
	size_t	i;
	char	*word;

	word = try_calloc(size + 1, sizeof(char));
	i = 0;
	while (i < size)
	{
		word[i] = line[i];
		i++;
	}
	return (word);
}

char	*token_get_type_word(char *word)
{
	char	*type_word;
	size_t	i;

	type_word = try_calloc(ft_strlen(word) + 1, sizeof(char));
	i = 0;
	while (word[i] != '\0')
	{
		type_word[i] = token_set_type_word(word[i]);
		i++;
	}
	return (type_word);
}

void	token_get_current_token(t_token **head, \
								char **line
								)
{
	t_token			*current_token;
	size_t			size;
	char			*word;
	t_token_type	current_token_type;

	while (ft_isspace(**line))
		(*line)++;
	if (**line == '\0')
		return ;
	size = token_get_current_word_size(*line);
	word = token_get_current_word(*line, size);
	current_token_type = token_set_flag_token(word);
	current_token = create_token(word, current_token_type);
	token_addback(head, current_token);
	*line += size;
}
