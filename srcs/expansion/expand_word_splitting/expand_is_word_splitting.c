/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_is_word_splitting.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:16:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/16 13:50:53 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
int		printf(const char *format, ...);
	// if (!expand_check_quote(&node->command_list->word_list) && \
	// 	!expand_check_quote(&node->command_list->word_list)&&
	// 	!expand_is_empty_ifs(ifs->value))
# define SPACE ' '
# define TAB '\t'
# define NEW_LINE '\n'


bool	expand_is_word_splitting(char *token, char *ifs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (token[i] != '\0')
	{
		while (ifs[j] != '\0')
		{
			if (token[i] == ifs[j])
				return (true);
			j++;
		}
		j = 0;
		i++;
	}
	return (false);
}

bool	expand_is_word_splitting_word_list(t_word_list *word_list, char *ifs)
{
	t_token_type	f_quote;

	while (word_list != NULL)
	{
		if (word_list->type == TOKEN_SINGLE_QUOTE || \
			word_list->type == TOKEN_DOUBLE_QUOTE)
		{
			f_quote = word_list->type;
			while (f_quote != word_list->type)
			{
				word_list = word_list->next;
				//quoteが奇数の場合の処理なので要相談
				if (word_list == NULL)
					return (true);
			}
		}
		else
		{
			// debug_bool_printf_test(expand_is_word_splitting(word_list->word, ifs), "is_word_splitting");
			// printf("word   %s\n", word_list->word);
			// printf("ifs    %s\n", ifs);
			if (expand_is_word_splitting(word_list->word, ifs) && \
				word_list->is_expand)
				return (true);
		}
		word_list = word_list->next;
	}
	return (false);
}

bool	expand_is_empty_ifs(char *ifs)
{
	if (ifs == NULL || ifs[0] == '\0')
		return (true);
	return (false);
}

char	*expand_set_ifs_default_char(int f_space, int f_tab, int f_new_line)
{
	char	*ifs_default_char;
	char	*tmp;
	size_t	size;

	size = f_space + f_tab + f_new_line;
	ifs_default_char = try_calloc(size + 1, sizeof(char));
	tmp = ifs_default_char;
	if (f_space)
	{
		*tmp = SPACE;
		tmp++;
	}
	if (f_tab)
	{
		*tmp = TAB;
		tmp++;
	}
	if (f_new_line)
	{
		*tmp = NEW_LINE;
		tmp++;
	}
	return (ifs_default_char);
}

char	*expand_check_ifs_default_char(char *ifs)
{
	int	f_space;
	int	f_tab;
	int	f_new_line;

	f_space = 0;
	f_tab = 0;
	f_new_line = 0;
	while (*ifs != '\0')
	{
		if (*ifs == SPACE)
			f_space = 1;
		if (*ifs == TAB)
			f_tab = 1;
		if (*ifs == NEW_LINE)
			f_new_line = 1;
		ifs++;
	}
	return (expand_set_ifs_default_char(f_space, f_tab, f_new_line));
}
