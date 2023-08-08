/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:21:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/08 16:28:16 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*expand_convert_doller_word(char **word, t_data *d)
{
	char	*expand_word;

	(*word)++;
	if (word == '?')
		expand_word = expand_get_exist_status(word, d->exit_status);
	else
		expand_word = expand_get_expand_word(word, d->envs_hashmap);
	return (expnad_word);
}

char	*expand_get_expanded_token_word(char *token_word, t_data *d)
{
	char	*expand_word;
	char	*join_word;

	join_word = NULL;
	while (*token_word)
	{
		if (*token_word == '$')
		{
			expand_word = expand_convert_doller_word(&token_word, d);
			join_word = expand_extend_str(join_word, token_word);
		}
		expand_word = ft_substr(&token_word, '$');
		join_word = expand_extend_str(join_word, expand_word);
		token_word ++;
	}
	return (join_word);
}

void	expand_token_word_list(t_word_list *token, t_data *d)
{
	char	*expand_word;

	expand_word = expand_get_expanded_token_word(token->word, t_data *d);
	free(token->word);
	token->word = expand_word;
}

void	expand_token_redirect_list(t_redirect *token, t_data *d)
{
	char	*expand_word;

	expand_word = get_expand_token_word(token->word, d);
	free(token->word);
	token->word = expand_word;
}

void	expand_variable_word_list(t_word_list *head, t_data *d)
{
	t_word_list		*ite;

	ite = head;
	while (ite != NULL)
	{
		if (ite->type == SINGLE_QUOTE || ite->type == DOUBLE_QUOTE)
		{
			while (ite->type != SINGLE_QUOTE && ite->type != DOUBLE_QUOTE)
				ite = ite->next;
		}
		if (ite->type == WORD && ft_strchr(ite->word, '$'))
			expand_token_word_list(ite, d);
		ite = ite->next
	}
}

void	expand_variable_redirect_list(t_redirect *head, t_data *d)
{
	t_redirect		*ite;

	ite = head;
	while (ite != NULL)
	{
		if (ite->type == SINGLE_QUOTE || ite->type == DOUBLE_QUOTE)
		{
			while (ite->type != SINGLE_QUOTE && ite->type != DOUBLE_QUOTE)
				ite = ite->next;
		}
		if (ite->type == WORD && ft_strchr(ite->word, '$'))
			expand_token_redirect_list(ite);
		ite = ite->next
	}
	
}

void	expand_variable(t_ast *node, t_data *d)
{
	t_ast		*node;

	expand_variable_word_list(node->command_list->word_list, d);
	expand_variable_redirect_list(node->command_list->redirect_list, d);
}
