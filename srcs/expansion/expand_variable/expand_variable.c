/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:21:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/27 19:57:53 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

bool	expand_is_str_in_char(char *str, char c)
{
	if (str == NULL)
		return (false);
	while (*str != '\0')
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

bool expand_is_variable_word(char *word)
{
	t_quote f_quote;
	size_t i;

	i = 0;
	if (word == NULL)
		return (false);
	while (word[i] != '\0')
	{
		f_quote = token_set_flag_quote(word[i]);
		if (f_quote == SINGLE_QUOTE_FLAG)
		{
			while (f_quote != token_set_flag_quote(word[++i]))
			{
				if (word[i] == '\0')
					return (false);
			}
			i++;
		}
		else
		{
			if (word[i] == '$')
				return (true);
			i++;
		}
	}
	return (false);
}

void expand_variable_word_list(t_word_list *word_list, t_data *d)
{
	char *expand_word;

	if (expand_is_variable_word(word_list->word))
	{

		// printf("word     %s\n", word_list->word);
		expand_get_expanded_token(&(word_list->word), &(word_list->type), d);
		// printf("expand   %s\n", expand_word);
	}
}

//"  aa"
//"  aa  d"bb
//cc"  aa  d"bb

bool expand_is_ambiguous_error(char *redirect_word, char *redirect_type, char *ifs)
{
	char	*ifs_default_char;
	size_t	i;
	bool	flag;

	if (redirect_word == NULL || redirect_type == NULL)
		return (false);
	ifs_default_char = expand_check_ifs_default_char(ifs);
	i = 0;
	flag = false;
	while (redirect_word[i] != '\0')
	{
		while (redirect_word[i] != '\0' && redirect_type[i] == '1')
		{
			while (redirect_word[i] != '\0' && redirect_type[i] == '1' && expand_is_str_in_char(ifs, redirect_word[i]))
			{
				printf("redirect_word  [%zu] \n", i);
				if (expand_is_str_in_char(ifs_default_char, redirect_word[i]))
				{
					i++;
					continue;
				}
				else
					return (true);
			}
			while (redirect_word[i] != '\0' && redirect_type[i] == '1')
			{
				printf("redirect_word  %c[%zu] \n",redirect_word[i], i);
				printf("redirect_word  [%zu] \n", i);
				printf("ifs            [%s] \n", ifs);
				if (!expand_is_str_in_char(ifs, redirect_word[i]))
				{
					i++;
					continue;
				}
				else
				{
					return (true);
				}
			}
		}
		if (redirect_word[i] == '\0')
			break;
		i++;
	}
	return (false);
}

void expand_variable_redirect_list(t_redirect_list *redirect_list, t_data *d)
{
	char *word;
	char *expand_word;
	char *ifs;
	bool is_empty_ifs;

	ifs = envs_get_value("IFS", d->envs_hashmap);
	is_empty_ifs = expand_is_empty_ifs(ifs);

	// is_abi trueかつ展開前の値が入る
	// 条件 expand_word_splitting
	// 通常の場合、展開後の値がIFSにある場合
	word = redirect_list->word;
	if (expand_is_variable_word(word))
	{
		// printf("word     %s\n", redirect_list->word);
		expand_get_expanded_token(&(redirect_list->word), &(redirect_list->type), d);
		printf("redirect   %s, %s\n", redirect_list->word, redirect_list->type);
		if (expand_is_ambiguous_error(redirect_list->word, redirect_list->type, ifs))
		{
			printf("expand   %s\n", word);
			printf("expand   %s\n", redirect_list->word);
			redirect_list->is_ambiguous_error = true;
			redirect_list->word = word;
		}

	}
}
