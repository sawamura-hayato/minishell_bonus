/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_expanded_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:02:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/15 14:30:04 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

int printf(const char *format, ...);
void	debug_printf_test(char *testA, char *testB);
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

	// printf("word   %s\n", *word);
	// exit(0);
	target_word = expand_get_string_to_dollar_or_symbol(word);
	target_value = envs_get_value(target_word, envs);
	return (target_value);
}

char *expand_convert_dollar_word(char **word, t_data *d)
{
	char *expand_word;

	expand_word = *word;
	(*word)++;
	if (**word == '\0')
		return (try_strdup(expand_word));
	else if (**word == '?')
		expand_word = expand_get_exist_status(word, d->exit_status);
	else
		expand_word = expand_get_expand_word(word, d->envs_hashmap);
	return (expand_word);
}

size_t expand_get_string_to_dollar_or_symbol_size(char *word)
{
	size_t size;

	size = 0;
	// printf("word   %s\n", word);
	// exit(0);
	while (word[size] != '\0' && (!export_is_symbol(word[size])) && \
			(!ft_isspace(word[size])))
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
	while (i < size)
	{
		str[i] = (*word)[i];
		i++;
	}
	(*word) += size;
	return (str);
}

size_t	expand_get_str_to_dollar_size(char *word)
{
	size_t	i;
	
	i = 0;
	while (word[i] != '\0' && word[i] != '$')
		i++;
	return (i);
}

char	*expand_get_str_to_dollar(char **word)
{
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	size = expand_get_str_to_dollar_size(*word);
	str = try_calloc(size + 1, sizeof(char));
	while (i < size)
	{
		str[i] = (*word)[i];
		i++;
	}
	*word += size;
	return (str);
}

char *expand_get_expanded_token(char *token, t_data *d)
{
	char *expand_word;
	char *join_word;

	join_word = NULL;
	while (*token != '\0')
	{
		if (*token == '$')
		{
			expand_word = expand_convert_dollar_word(&token, d);
			join_word = try_strjoin_free(join_word, expand_word);
			free(expand_word);
		}
		else
		{
			expand_word = expand_get_str_to_dollar(&token);
			join_word = try_strjoin_free(join_word, expand_word);
			free(expand_word);
		}
	}
	return (join_word);
}

// int main(void)
// {
// 	extern const char **environ;
// 	t_data data;

// 	data.exit_status = 0;
// 	envs_init(environ, &data);
// 	//末尾に空白を入れたらokになる
// 	debug_printf_test("", expand_get_expanded_token("$B", &data));
// 	debug_printf_test("?llll ", expand_get_expanded_token("$ABV?llll", &data));
// 	debug_printf_test("B+++", expand_get_expanded_token("$A+++$B", &data));
// 	debug_printf_test("echo      B", expand_get_expanded_token("echo   $D  $A", &data));
// 	debug_printf_test("B", expand_get_expanded_token("$B$A", &data));
// 	debug_printf_test("sawamurashunsawamurashun", expand_get_expanded_token("$USER$USER", &data));
// 	debug_printf_test("/opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/opt/X11/bin:/opt/homebrew/bin:/opt/homebrew/sbin", expand_get_expanded_token("$BD$PATH", &data));
// 	// printf("output   %s\n", expand_get_expanded_token("$B$A$", &data));
// 	// printf("output   %s\n", expand_get_expanded_token("$B$A", &data));
// 	// printf("output   %s\n", expand_get_expanded_token("$B$A", &data));
// 	return (0);
// }
