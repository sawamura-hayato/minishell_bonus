/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:23 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/23 19:20:25 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
#define EXPANSION_H

#include "parse.h"
#include "init.h"
#include <stdlib.h>

int printf(const char *format, ...);

// expansion.c
void expansion(t_ast *node, t_data *d);

// expand_variable
void expand_variable(t_ast *node, t_data *d);
char *expand_convert_dollar_word(char **word, t_data *d);
char *expand_get_expanded_token(char *token_word, t_data *d);
void expand_token_word_list(t_word_list *token, t_data *d);
void expand_token_redirect_list(t_redirect_list *token,
								t_data *d,
								t_redirect_type is_quote);
void expand_variable_word_list(t_word_list **head, t_data *d);
void expand_variable_redirect_list(t_redirect_list **head, t_data *d);
void expand_dollar_quote_string_word_list(t_word_list **head);
t_word_list *expand_can_dollar_quote_string_word_list(t_word_list **head);
t_redirect_list *expand_can_dollar_quote_string_redirect(t_redirect_list **head);

// delete_word_list.c
void word_list_free(t_word_list *word_list);
void word_list_delete_head(t_word_list **head);
void word_list_delete_tail(t_word_list **head);
void word_list_delete_target(t_word_list **head, t_word_list *target);

// delete_redirect.c
void redirect_free(t_redirect_list *redirect);
void redirect_delete_head(t_redirect_list **head);
void redirect_delete_tail(t_redirect_list **head);
void redirect_delete_target(t_redirect_list **head, t_redirect_list *target);

// expand_word_splitting.c
// IFSを確認 クオテーションで囲まれていない && スペースがある場合、線形リストのトークンを分割
void expand_word_splitting(t_ast *node, t_data *d);
//  char	*expand_get_splitting_word(char **word);
//  void	expand_get_splitting_word_list(t_word_list **word_list);
//  void	expand_splitting_word_list(t_word_list *word_list, t_envs *ifs);
//  void	expand_splitting_redirect_list(t_redirect_list *redirect_list, t_envs *ifs);
//  void	expand_word_splitting(t_ast *node, t_data *d);

// expand_filename.c
void expand_filename(t_ast *node);
void expand_filename_word_list(t_word_list *word_list);
void expand_filename_redirect_list(t_redirect_list redirect_list);
bool expand_is_wildcard(char *word);
bool expand_is_filename_word(char *word, char *target);
void word_list_insert_target(t_word_list *word_list, char *taget);
bool expand_is_filename_word(char *word, char *target);
size_t expand_filename_word_list_size(t_word_list *word_list);
void expand_can_get_filename_word_list(t_word_list *word_list);

// expand_delete_quote.c
void expand_delete_quotation(t_ast *node);
void word_list_delete_target_type(t_word_list *word_list, t_token_type taget);
void redirect_list_delete_target_type(t_word_list *word_list, t_token_type taget);
void expandion_delete_quotation_word_list(t_word_list *word_list);
void expandion_delete_quotation_redirect_list(t_redirect_list *redirect_list);

// expand_debug.c
t_ast *debug_new_ast(t_command *command, t_ast_node_type type);
t_command *debug_new_command(t_word_list *word_list, t_redirect_list *redirect_list);
t_word_list *debug_new_word_list(char *word, size_t index, t_token_type type);
t_redirect_list *debug_new_redirect_list(char *word, size_t index, t_redirect_type type);

void debug_printf_word_list(t_word_list *word_list);
void debug_free_word_list(t_word_list *word_list);
void debug_printf_redirect(t_redirect_list *redirect);
void debug_free_redirect(t_redirect_list *redirect);
#endif
