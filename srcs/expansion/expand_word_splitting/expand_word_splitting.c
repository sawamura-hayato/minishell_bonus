/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:30:36 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/21 12:50:52 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*envs_get_value(char *_key, t_envs **envs_hashmap);
int		printf(const char *format, ...);
// char *expand_get_splitting_word(char **word)
// {
// 	// "    aa bbbb"     aa
// 	// " bbbb"           bbbb
// 	// " ddd  ee  c  "   ddd
// 	// "  ee  c  "       ee
// 	// "  c  "           c
// 	// "  "              NULL
// }

// void expand_get_splitting_word_list(t_word_list **word_list)
// {
// 	t_word_list *new_word_list;
// 	char *tmp_word;
// 	char *splitting_word;

// 	tmp_word = (*word_list)->word;
// 	(*word_list)->word = expand_get_splitting_word(&tmp_word);
// 	while (*tmp_word)
// 	{
// 		splitting_word = expand_get_splitting_word(&tmp_word);
// 		if (splitting_word != NULL)
// 		{
// 			new_word_list = ast_init_word_node(splitting_word);
// 			(*word_list)->next = new_word_list;
// 			*word_list = (*word_list)->next;
// 		}
// 	}
// 	free(tmp_word);
// }

// ifsに空白、タブ、改行が設定されている場合は
// - 設定されてる対象のみ単語分割することができる（トークンを分ける）
// - 前後にある場合は削除する
// それ以外の文字が任意で設定されている場合は
// - 任意の文字が連続している場合、または前後に任意の文字があった場合ははNULL文字のトークンを作成する。
// - 任意の文字が設定されてない文字同士の間にある場合は単語分割する（トークンを分ける）

static bool	is_str_in_char(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

	// デフォルトなしの場合
	// aabbaccaadd
	// ifs = a
	// NULL->NULL->bb->cc->NULL->dd
	// デフォルトありの場合
	// bba ccaadd
	// ifs = a
	// bba
	// ccaadd
	// bb
	// ccaadd
	// cca
	// NULL
	// dd
// 	// bb->cc->NULL->dd
size_t	expand_get_size_word_splitting_word_by_not_ifs_default_char(char *word, char *ifs_default_char)
{
	size_t	i;

	i = 0;
	while (!is_str_in_char(ifs_default_char, word[i]) && word[i] != '\0')
		i++;
	return (i);
}

char	*expand_get_word_splitting_word_by_not_ifs_default_char(char **word, char *ifs)
{
	char	*new_word;
	size_t	size;
	size_t	i;

	size = expand_get_size_word_splitting_word_by_not_ifs_default_char(*word, ifs);
	new_word = try_calloc(size + 1, sizeof(char));
	i = 0;
	while (i < size)
	{
		new_word[i] = (*word)[i];
		i++;
	}
	printf("word   %s\n", *word);
	printf("size   %zu\n", size);
	(*word) += size;
	return (new_word);
}

size_t	expand_get_size_arr_in_splitting_word_by_not_ifs_default_char(char *word, char *ifs_default_char)
{
	size_t	i;

	i = 1;
	while (*word != '\0')
	{
		if(is_str_in_char(ifs_default_char, *word))
		{
			word++;
			while (is_str_in_char(ifs_default_char, *word))
			{
				if (*word == '\0')
					break;
				word++;
			}
			i++;
		}
		else
			word++;
	}
	return (i);
}



char	**expand_get_arr_in_splitting_word_by_not_ifs_default_char(char *word, char *ifs)
{
	char	**arr;
	size_t	size;
	size_t	i;

	// printf("arr word%s\n",word);
	size = expand_get_size_arr_in_splitting_word_by_not_ifs_default_char(word, ifs);
	// printf("arr size%zu\n",size);
	arr = try_malloc((size + 1) * sizeof(char *));
	i = 0;
	arr[size] = NULL;
	while (arr[i] != NULL)
	{
		arr[i] = expand_get_word_splitting_word_by_not_ifs_default_char(&(word), ifs);
		printf("arr[%zu] %s\n", i, arr[i]);
		i++;
	}
	return (arr);
}

void	expand_splitting_word_list_by_ifs_not_default_char(t_word_list **node, char *ifs)
{
	char	*tmp;

	tmp = (*node)->word;
	// printf("tmp %s\n", tmp);
	if (*tmp == '\0')
		return ;
	(*node)->word = expand_get_word_splitting_word_by_not_ifs_default_char(&(tmp), ifs);
	while (*tmp != '\0')
	{
		if (is_str_in_char(ifs, *tmp))
		{
			tmp++;
			while (is_str_in_char(ifs, *tmp))
			{
				word_list_new_target(node, *node, debug_new_word_list(try_strdup(""), 0, WORD));
				(*node) = (*node)->next;
				tmp++;
			}
			if (*tmp == '\0')
				continue;
			word_list_new_target(node, *node, debug_new_word_list(expand_get_word_splitting_word_by_not_ifs_default_char(&(tmp), ifs), (*node)->index, (*node)->type));
			(*node) = (*node)->next;
			(*node)->is_expand = true;
		}
	}
}

// 任意の文字列が前後に連続してある場合に削除する関数
char	*expand_check_delete_front_and_back_position(char *word, char *ifs_default_char)
{
	char	*new_word;
	size_t	start_index;
	size_t	end_index;
	size_t	size;
	size_t	i;

	start_index = 0;
	while (is_str_in_char(ifs_default_char, word[start_index]))
		start_index++;
	end_index = ft_strlen(word);
	while (is_str_in_char(ifs_default_char, word[end_index - 1]))
		end_index--;
	size = end_index - start_index + 1;
	new_word = try_calloc(size, sizeof(char));
	i = 0;
	while (start_index + i < end_index)
	{
		new_word[i] = word[start_index + i];
		i++;
	}
	return (new_word);
}

size_t	expand_get_size_word_splitting_word(char *word, char *ifs_default_char)
{
	size_t	i;

	i = 0;
	while (!is_str_in_char(ifs_default_char, word[i]) && word[i] != '\0')
		i++;
	return (i);
}

char	*expand_get_word_splitting_word(char **word, char *ifs_default_char)
{
	char	*new_word;
	size_t	i;
	size_t	size;

	size = expand_get_size_word_splitting_word(*word, ifs_default_char);
	new_word = try_calloc(size + 1, sizeof(char));
	i = 0;
	while (i < size)
	{
		new_word[i] =  (*word)[i];
		i++;
	}
	(*word) += size;
	while (is_str_in_char(ifs_default_char, (**word)))
		(*word) ++;
	return (new_word);
}

size_t	expand_get_size_arr_in_splitting_word(char *word, char *ifs_default_char)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 1;
	while (word[i] != '\0')
	{
		if(is_str_in_char(ifs_default_char, word[i]))
		{
			size++;
			while (is_str_in_char(ifs_default_char, word[i]))
				i++;
		}
		else
			i++;
	}
	return (size);
}


char	**expand_get_arr_in_splitting_word(char *word, char *ifs_default_char)
{
	char	**arr;
	size_t	size;
	size_t	i;

	size = expand_get_size_arr_in_splitting_word(word, ifs_default_char);
	arr = try_malloc((size + 1) * sizeof(char *));
	i = 0;
	arr[size] = NULL;
	while (arr[i] != NULL)
	{
		arr[i] = expand_get_word_splitting_word(&(word), ifs_default_char);
		printf("arr[%zu]  %s\n", i, arr[i]);
		// word = expand_check_delete_front_and_back_position(word, ifs_default_char);
		i++;
	}
	return (arr);
}

void	expand_splitting_word_list_by_ifs_default_char(t_word_list **word_list, char *ifs_default_char)
{
	char		**arr;
	t_word_list	*node;
	size_t		i;

	node = *word_list;
	// free((*word_list)->word);
	// printf("word%sd\n",(*word_list)->word);
	(*word_list)->word = expand_check_delete_front_and_back_position((*word_list)->word, ifs_default_char);
	// printf("word%sd\n",(*word_list)->word);
	arr = expand_get_arr_in_splitting_word((*word_list)->word, ifs_default_char);
	// free((*word_list)->word);
	(*word_list)->word = arr[0];
	i = 1;
	while (arr[i] != NULL)
	{
		word_list_new_target(word_list, (*word_list), debug_new_word_list(arr[i], (*word_list)->index, (*word_list)->type));
		(*word_list) = (*word_list)->next;
		(*word_list)->is_expand = true;
		i++;
	}
	*word_list = node;
}

void expand_splitting_word_list(t_word_list **word_list, char *ifs, char *ifs_default_char)
{
	t_word_list	*node;
	t_word_list	*pre_node;
	// t_word_list	*tmp_node;

	node = *word_list;
	pre_node = NULL;
	while (node != NULL)
	{
		if (expand_is_word_splitting(node->word, ifs) && \
				node->is_expand)
		{
			if (ifs_default_char != NULL)
				expand_splitting_word_list_by_ifs_default_char(&node, ifs_default_char);
			node->word++;
			while (*(node->word) != '\0' && is_str_in_char(ifs, *(node->word)))
			{
				if (pre_node == NULL)
				{
					word_list_new_tail(&pre_node, debug_new_word_list(try_strdup(""), 0, WORD));
					pre_node->next = (*word_list);
					(*word_list) = pre_node;
				}
				else
				{
					word_list_new_target(&pre_node, pre_node, debug_new_word_list(try_strdup(""), 0, WORD));
					// printf("word_list \n");
					// debug_printf_word_list(*word_list);
					// printf("pre_node \n");
					// debug_printf_word_list(pre_node);
					pre_node = pre_node->next;
				}
				node->word++;
			}
			expand_splitting_word_list_by_ifs_not_default_char(&node, ifs);
			// printf("word_list \n");
			// debug_printf_word_list(*word_list);
			// printf("pre_node \n");
			// debug_printf_word_list(pre_node);
			// printf("node \n");
			// debug_printf_word_list(node);
			// printf("word_list \n");
			// debug_printf_word_list(*word_list);
			// printf("pre_node \n");
			// debug_printf_word_list(pre_node);
			// printf("node \n");
			// debug_printf_word_list(node);
			// exit(0);
			// printf("nod   %s\n", node->word);
		}
		pre_node = node;
		node = node->next;
	}
}

// void expand_splitting_redirect_list(t_redirect_list *redirect_list, char *ifs)
// {
// }

void expand_word_splitting(t_ast *node, t_data *d)
{
	char *ifs;
	bool is_empty_ifs;
	char *check_ifs_default_char;

	ifs = envs_get_value("IFS", d->envs_hashmap);
	is_empty_ifs = expand_is_empty_ifs(ifs);
	// クウォートがある場合、IFS の値が空文字列の場合（IFS=, IFS='', IFS=""）
	check_ifs_default_char = NULL;
	if (!is_empty_ifs && \
		expand_is_word_splitting_word_list(node->command_list->word_list, ifs))
	{
		check_ifs_default_char = expand_check_ifs_default_char(ifs);
		expand_splitting_word_list(&(node->command_list->word_list), ifs, check_ifs_default_char);
	}
	// if (expand_is_word_spliting_redirect_list(node->command_list->redirect_list) && \
	// 	!is_empty_ifs)
	// 	expand_splitting_redirect_list(&(node->command_list->redirect_list), ifs);
	free(check_ifs_default_char);
	// (void)node;
	// (void)d;
}

// int main(void)
// {
// 	// printf("ifs   %s\n", expand_check_ifs_default_char("aa df ae e"));
// 	// printf("ifs   %s\n", expand_check_ifs_default_char("aa df ae\nne"));
// 	t_word_list	*word_list;
// 	word_list = debug_new_word_list("word_splitting", 1, WORD);
// 	word_list->is_expand = true;

// 	// quote flagがない場合
// 	// // printf("ifs   %s\n", expand_check_ifs_default_char("aa df\tae e\t"));
// 	// // printf("ifs   %s\n", expand_check_ifs_default_char("aadf\taee\n"));
// 	// debug_bool_printf_test(!expand_is_word_splitting_word_list(word_list, "fa\n"), "word_splitting");
// 	// debug_bool_printf_test(expand_is_word_splitting_word_list(word_list, " t "), "word_splitting");
// 	// debug_bool_printf_test(expand_is_word_splitting_word_list(word_list, "_"), "word_splitting");
	
// 	// quote flagがある場合
// 	// word_list = debug_new_word_list("\"", 1, TOKEN_DOUBLE_QUOTE);
// 	// word_list->is_expand = true;
// 	// word_list->next = debug_new_word_list("word_splitting", 1, WORD);
// 	// word_list->next->next = debug_new_word_list("\"", 1, TOKEN_DOUBLE_QUOTE);
// 	// debug_bool_printf_test(!expand_is_word_splitting_word_list(word_list, "fa\n"), "word_splitting");
// 	// debug_bool_printf_test(!expand_is_word_splitting_word_list(word_list, " t "), "word_splitting");
// 	debug_bool_printf_test(!expand_is_word_splitting_word_list(word_list, NULL), "word_splitting");
// 	return (0);
// }
