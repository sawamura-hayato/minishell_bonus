/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:48:38 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/26 12:59:08 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdlib.h>

t_token	*init_token(size_t n_token)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->word = init_word();
	token->operator = WORD;
	token->n_token = n_token;
	token->next = NULL;
	return (token);
}

t_token	*create_token(t_word word, t_operator_type operator, size_t n_token)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->word = word;
	token->operator = operator;
	token->n_token = n_token;
	token->next = NULL;
	return (token);
}

void	debug_print_token(t_token *token_list)
{
	while (token_list != NULL)
	{
		printf("word            [%s]\n", token_list->word.word);
		printf("word type       [%d]\n", token_list->word.type);
		printf("token operator  [%d]\n", token_list->operator);
		printf("token n         [%zu]\n", token_list->n_token);
		token_list = token_list->next;
	}
}

void	free_token(t_token *token_list)
{
	t_token	*tmp_token;

	tmp_token = token_list->next;
	while (token_list != NULL)
	{
		free(token_list);
		token_list = tmp_token;
		tmp_token = token_list->next;
	}
}

// int main(int argc, char *argv[])
// {
// 	t_token *token;

// 	token = create_token(create_word(argv[1], DEFAULT), WORD, 0);
// 	debug_print_token(token);
// 	return (0);
// }
