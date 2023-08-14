/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:21:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/14 19:00:52 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
// #include <stdio.h>

int printf(const char *format, ...);

char *expand_convert_doller_word(char **word, t_data *d)
{
	// char	*expand_word;

	// (*word)++;
	// if (*word == '?')
	// 	expand_word = expand_get_exist_status(word, d->exit_status);
	// else
	// 	expand_word = expand_get_expand_word(word, d->envs_hashmap);
	// return (expand_word);
	(void)d;
	return (*word);
}

char *expand_get_expanded_token_word(char *token_word, t_data *d)
{
	// char	*expand_word;
	// char	*join_word;

	(void)d;
	return (token_word);
	// join_word = NULL;
	// while (*token_word)
	// {
	// 	if (*token_word == '$')
	// 	{
	// 		expand_word = expand_convert_doller_word(&token_word, d);
	// 		join_word = expand_extend_str(join_word, token_word);
	// 	}
	// 	expand_word = ft_substr(&token_word, '$');
	// 	join_word = expand_extend_str(join_word, expand_word);
	// 	token_word ++;
	// }
	// return (join_word);
}

void expand_token_word_list(t_word_list *token, t_data *d)
{
	char *expand_word;

	expand_word = expand_get_expanded_token_word(token->word, d);
	free(token->word);
	token->word = expand_word;
}

void expand_token_redirect_list(t_redirect *token, t_data *d, t_redirect_type is_quote)
{
	char *expand_word;

	// expand_word = get_expand_token_word(token->word, d);
	(void)token;
	(void)d;
	(void)expand_word;
	(void)is_quote;
	// 環境変数がない場合, トークンが複数に分かれる場合
	// if (is_quote != RD_DOUBLE_QUOTE && \
	// 	(expand_word == NULL || expand_is_tokens(expand_word)))
	// {
	// 	free(expand_word);
	// 	// token->is_abm_error = true;
	// }
	// else
	// {
	// 	free(token->word);
	// 	token->word = expand_word;
	// }
}

void	word_list_free(t_word_list *word_list)
{
	// free(word_list->word);
	free(word_list);
}

void word_list_delete_head(t_word_list **head)
{
	t_word_list	*node;
	t_word_list	*tmp;

	node = *head;
	tmp = node->next;
	word_list_free(node);
	*head = tmp;
}

void word_list_delete_tail(t_word_list **head)
{
	t_word_list	*node;

	node = *head;
	if (node == NULL || node->next == NULL)
		return ;
	while (node->next->next != NULL)
		node = node->next;
	word_list_free(node->next);
	node->next = NULL;
}

void	word_list_delete_taget(t_word_list **head, t_word_list *target)
{
	t_word_list	*tmp;
	t_word_list	*node;

	node = *head;
	while (node->next != NULL && ft_strcmp(node->next->word, target->word))
		node = node->next;
	if (node->next != NULL)
	{
		tmp = node->next->next;
		word_list_free(node->next);
		node->next = tmp;
	}
}

void	expand_delete_dollar_quote(t_word_list **head, bool is_head_dollar)
{
	t_word_list	*node;

	node = *head;
	if (is_head_dollar)
	{
		// $ ' aaa '
		word_list_delete_head(head);
		word_list_delete_head(head);
		// aaa '
		// if ((*head)->next->next == NULL)
		// 	word_list_delete_tail(head);
		// else
		word_list_delete_taget(head, (*head)->next);
	}
	else
	{
		// exit(0);
		// echo $ ' aaa '
		// echo ' aaa '
		while (ft_strcmp((*head)->next->word, "$"))
			(*head) = (*head)->next;
		word_list_delete_taget(head, (*head)->next);
		// echo aaa '
		word_list_delete_taget(head, (*head)->next);
		// echo aaa
		if ((*head)->next->next == NULL)
			word_list_delete_tail(head);
		else
			word_list_delete_taget(head, (*head)->next->next);
		(*head) = node;
	}
}

void	expand_dollar_quote_string(t_word_list **head)
{
	t_word_list *node;

	if (!ft_strcmp((*head)->word, "$") && \
		((*head)->next->type == SINGLE_QUOTE || (*head)->next->type == DOUBLE_QUOTE))
		expand_delete_dollar_quote(head, true);
	node = *head;
	while ((*head) != NULL && (*head)->next != NULL && (*head)->next->next != NULL)
	{
		if (!ft_strcmp((*head)->next->word, "$") && \
			((*head)->next->next->type == SINGLE_QUOTE || \
				(*head)->next->next->type == DOUBLE_QUOTE))
		{
			expand_delete_dollar_quote(head, false);
			// exit(0);
			// *head = node;
		}
		*head = (*head)->next;
	}
	*head = node;
}

bool	expand_is_dollar_quote_string(t_word_list *head)
{
	t_word_list *node;

	node = head;
	if (node == NULL || node->next == NULL)
		return (false);
	if (!ft_strcmp(node->word, "$") && \
		(node->next->type == SINGLE_QUOTE || node->next->type == DOUBLE_QUOTE))
		return (true);
	while (node->next->next != NULL)
	{
		if (!ft_strcmp(node->next->word, "$") && \
			(node->next->next->type == SINGLE_QUOTE || node->next->next->type == DOUBLE_QUOTE))
			return (true);
		node = node->next;
	}
	return (false);
}

t_word_list	*expand_can_dollar_quote_string(t_word_list **head)
{
	if (expand_is_dollar_quote_string(*head))
		expand_dollar_quote_string(head);
	return (*head);
}

void expand_variable_word_list(t_word_list **head, t_data *d)
{
	t_word_list		*node;
	(void)head;
	(void)d;

	// if (ft_strcmp((*head)->word, "ok") == 0)
	// 	exit(0);
	node = expand_can_dollar_quote_string(head);
	(void)node;
	// while (node != NULL)
	// {
	// 	if (node->type == SINGLE_QUOTE)
	// 	{
	// 		node = node->next;
	// 		while (node->type != SINGLE_QUOTE)
	// 			node = node->next;
	// 	}
	// 	// if (node->type == WORD && ft_strchr(node->word, '$'))
	// 	// 	expand_token_word_list(node, d);
	// 	node = node->next;
	// }
}

void expand_variable_redirect_list(t_redirect **head, t_data *d)
{
	// t_redirect		*node;

	(void)head;
	(void)d;
	// node = expand_dollar_quote_string_redirect(head);
	// while (node != NULL)
	// {
	// 	if (node->type == RD_SINGLE_QUOTE)
	// 	{
	// 		node = node->next;
	// 		while (node->type != RD_SINGLE_QUOTE)
	// 			node = node->next;
	// 	}
	// 	// if (node->type != RD_SINGLE_QUOTE && ft_strchr(node->word, '$'))
	// 	// 	expand_token_redirect_list(node, d, node->type);
	// 	node = node->next;
	// }
}

void expand_variable(t_ast *node, t_data *d)
{
	if (node->command_list != NULL)
	{
		expand_variable_word_list(&(node->command_list->word_list), d);
		// expand_variable_redirect_list(&(node->command_list->redirect_list), d);
	}
	else
		printf("operator\n");
}
