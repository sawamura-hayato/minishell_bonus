/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/22 12:36:25 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_word	create_word(char *new_word, t_word_type type)
{
	t_word	word;

	word.word = new_word;
	word.type = type;
	return (word);
}

int main(void)
{
	t_word word;

	word = create_word("DEFAULT", DEFAULT);
	printf("word test %s, word type %d\n", word.word, word.type);
	word = create_word("ODD SNGL", 	ODD_SINGL_QUOTE);
	printf("word test %s, word type %d\n", word.word, word.type);
	word = create_word("ODD DOUBLE", ODD_DOBULE_QUOTE);
	printf("word test %s, word type %d\n", word.word, word.type);
	return (0);
}
