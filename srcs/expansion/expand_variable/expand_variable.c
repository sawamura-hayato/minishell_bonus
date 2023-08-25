/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:21:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/25 20:47:49 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
// #include <stdio.h>

// int printf(const char *format, ...);
// void debug_printf_test(char *testA, char *testB);

// void expand_variable(t_ast *node, t_data *d)
// {
// 	expand_variable_word_list(&(node->command_list->word_list), d);
// 	expand_variable_redirect_list(&(node->command_list->redirect_list), d);
// }

bool	expand_is_variable_word(char *word)
{
	t_quote	f_quote;
	size_t	i;

	i = 0;
	if (word == NULL)
		return (false);
	f_quote = token_set_flag_quote(word[i]);
	while (word[i] != '\0')
	{
		if (f_quote != DEFAULT)
		{
			while (f_quote != token_set_flag_quote(word[++i]))
			{
				if (word[i] == '\0')
					break;
			}
		}
		else
		{
			if (word[i] == '$' && word[i + 1] != '\0')
				return (true);
			i++;
		}
	}
	return (false);
}

void	expand_variable_word_list(t_word_list *word_list, t_data *d)
{
	char	*expand_word;

	expand_word = word_list->word;
	while (expand_is_variable_word(expand_word))
	{
		// free(expand_word);
		printf("ok  %s\n", expand_word);
		expand_word = expand_get_expanded_token(expand_word, d);
	}
	word_list->word = expand_word;
}
