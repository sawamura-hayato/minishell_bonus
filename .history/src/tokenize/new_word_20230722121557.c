/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:46:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/22 12:15:57 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_word	new_word(char *new_word, t_word_type type)
{
	t_word	word;

	word.word = new_word;
	word.type = type;
	return (word);
}

int main(void)
{
	t_word word;

	word = new_word("ddd", DEFALUT);
	printf("word test   %s\n")
	printf("d");
	return (0);
}
