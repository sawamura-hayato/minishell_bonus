/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_expanded_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:02:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/14 23:53:35 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int printf(const char *format, ...);
bool export_is_symbol(char c);
char *expand_get_string_to_dollar_or_symbol(char **word);

char *expand_get_exist_status(char **word, unsigned int exit_status)
{
	(*word)++;
	return (try_itoa(exit_status));
}

char *expand_get_expand_word(char **word, t_envs **envs)
{
	char *target_word;
	char *target_value;

	printf("word   %s\n", *word);
	exit(0);
	target_word = expand_get_string_to_dollar_or_symbol(word);
	target_value = envs_get_value(target_word, envs);
	// if (target_value != NULL)
	// while
	return (target_value);
	// return ();
}

char *expand_convert_dollar_word(char **word, t_data *d)
{
	char *expand_word;

	(*word)++;
	if (**word == '?')
		expand_word = expand_get_exist_status(word, d->exit_status);
	else
		expand_word = expand_get_expand_word(word, d->envs_hashmap);
	return (expand_word);
}

size_t expand_get_string_to_dollar_or_symbol_size(char *word)
{
	size_t size;

	size = 0;
	if ()
	while (word[size] != '\0' && (!export_is_symbol(word[size])))
		size++;
	return (size);
}

char *expand_get_string_to_dollar_or_symbol(char **word)
{
	char *str;
	size_t size;
	size_t i;

	size = expand_get_string_to_dollar_or_symbol_size(*word);
	i = 0;
	str = try_calloc(size + 1, sizeof(char));
	while (i <= size)
	{
		str[i] = **word;
		(*word)++;
		i++;
	}
	(*word) += size;
	return (str);
}

char *expand_get_expanded_token(char *token, t_data *d)
{
	char *expand_word;
	char *join_word;

	join_word = NULL;
	while (*token != '\0')
	{
		while (export_is_symbol(*token) && *token != '\0')
		{
			if (*token == '$')
			{
				expand_word = expand_convert_dollar_word(&token, d);
				join_word = try_strjoin_free(join_word, expand_word);
				free(expand_word);
			}
			token++;
		}
		// if (*token == '$')
		// {
		// }
		// // printf
		// exit(0);
	}
	return (join_word);
}

int main(void)
{
	extern const char **environ;
	t_data data;

	data.exit_status = 0;
	envs_init(environ, &data);
	//$A+++$B
	//$A
	//+++
	//$B

	//$ABV?llll
	//$ABV
	//?llll

	//target envの場合はexport_is_symbol
	//それ以外の結合文字列は
	//先頭が＄以外だったら文字列作る。
	//先頭が＄の場合　target envに戻る
	printf("expand word   %s\n", expand_get_expanded_token("$B$A", &data));
	printf("expand word   %s\n", expand_get_expanded_token("ABBD$A", &data));
	printf("expand word   %s\n", expand_get_expanded_token("$BD$PATH", &data));
	printf("expand word   %s\n", expand_get_expanded_token("echo$D", &data));
	// printf("expand word   %s\n", expand_get_expanded_token("$B$A", &data));
	// printf("expand word   %s\n", expand_get_expanded_token("$B$A", &data));
	// printf("expand word   %s\n", expand_get_expanded_token("$B$A", &data));
	return (0);
}
