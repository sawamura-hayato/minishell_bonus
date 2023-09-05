/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:23 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/05 15:48:22 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "library.h"
# include "parse.h"
# include "init.h"
# include <stdlib.h>

// expansion.c
void			expansion(t_ast *node, t_data *d);

// expand_variable
void			expand_variable(t_ast *node, t_data *d);
void			expand_word_list(t_word_list **word_list, t_data *d);
void			expand_redirect_list(
					t_redirect_list **redirect_list, t_data *d);
char			*expand_convert_dollar_word(char **word, t_data *d);
void			expand_get_expanded_token(char **token, char **type, t_data *d);
void			expand_variable_word_list(t_word_list *word_list, t_data *d);
void			expand_variable_redirect_list(t_redirect_list *head, t_data *d);
void			expand_dollar_quote_string_word_list(t_word_list **head);
t_word_list		*expand_can_dollar_quote_string_word_list(t_word_list **head);
t_redirect_list	*expand_can_dollar_quote_string_redirect(
					t_redirect_list **head);
char			*expand_get_delete_dollar_quote(char **word, t_quote f_quote);
bool			expand_is_variable_word(char *word, char *type);
char			*expand_get_expand_word(char **word, t_envs **envs);

bool			expand_is_str_in_char(char *str, char c);
void			expand_get_joined(char **expand, char **join_word, \
							char **join_type, bool is_expand);
bool			expand_is_ambiguous_error(char *redirect_word, \
									char *redirect_type, \
									char *ifs);

// new_word_list.c
void			word_list_new_head(t_word_list **head,
					t_word_list *new_word_list);
void			word_list_new_tail(t_word_list **head,
					t_word_list *new_word_list);
void			word_list_new_target(t_word_list **head,
					t_word_list *target, t_word_list *new_word_list);

// delete_word_list.c
void			word_list_free(t_word_list *word_list);
void			word_list_delete_head(t_word_list **head);
void			word_list_delete_tail(t_word_list **head);
void			word_list_delete_target(t_word_list **head,
					t_word_list *target);

// delete_redirect.c
void			redirect_free(t_redirect_list *redirect);
void			redirect_delete_head(t_redirect_list **head);
void			redirect_delete_tail(t_redirect_list **head);
void			redirect_delete_target(t_redirect_list **head,
					t_redirect_list *target);

// expand_get_exit_status.c
char			*expand_get_exit_status(char **word, unsigned int exit_status);

// expand_get_str_to_dollar.c
char			*expand_get_str_to_dollar(char **word, char *type);
char			*expand_get_string_to_dollar_or_symbol(char **word);

void			expand_get_joined_convert_dollar_word(char **join_word, \
													char **join_type, \
													char **tmp, \
													t_data *d);

void			expand_get_joined_str_to_dollar(char **join_word, \
													char **join_type, \
													char **tmp, \
													char **tmp_type);

// expand_word_splitting.c
// IFSを確認 クオテーションで囲まれていない && スペースがある場合、線形リストのトークンを分割
void			expand_word_splitting(t_ast *node, t_data *d);

bool			expand_is_word_splitting(char *word, char *type, char *ifs);
bool			expand_is_word_splitting_word(char *word,
					char *type, char *ifs);
bool			expand_is_empty_ifs(char *ifs);
char			*expand_check_ifs_default_char(char *ifs);
void			expand_splitting_word_list(t_word_list **word_list,
					char *ifs, char *ifs_default_char);
bool			expand_is_quoted(char *type, size_t size);
bool			expand_have_ifs(char *word, char *ifs);
void			expand_word_splitting_word_list(t_word_list *node, char *ifs);
void			expand_word_splitting_redirect_list(t_redirect_list *node,
					char *ifs);

// expand_filename.c
void			expand_filename(t_ast *node);
void			expand_filename_word_list(t_word_list *node,t_data *d);
void			expand_filename_redirect(t_redirect_list *node,t_data *d);

//＊以下まで設計自由に変更してください！
bool			expand_is_wildcard(char *word);
bool			expand_is_filename_word(char *word, char *target);
void			word_list_insert_target(t_word_list *word_list, char *taget);
bool			expand_is_filename_word(char *word, char *target);
size_t			expand_filename_word_list_size(t_word_list *word_list);
void			expand_can_get_filename_word_list(t_word_list *word_list);
//＊

// expand_pathname_wordlist.c
t_word_list		*expand_pathname_wordlist(t_word_list **head,
					t_word_list *node, t_data *d);
t_redirect_list	*expand_pathname_redirectlist(t_redirect_list **head,
					t_redirect_list *node, t_data *d);

// expand_delete_quote.c
void			expand_delete_quotation(t_ast *node);
void			expand_delete_quotation_word_list(t_word_list *word_list);
void			expand_delete_quotation_redirect_list(
					t_redirect_list *redirect_list);
bool			expand_is_delete_quotation_word(char *word);
bool			expand_is_type_quotation(char type);
size_t			expand_get_size_delete_quotation_word(char *word);

//library
char			*try_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t end);

// expand_debug.c
t_ast			*debug_new_ast(t_command *command, t_ast_node_type type);
t_command		*debug_new_command(t_word_list *word_list,
					t_redirect_list *redirect_list);
t_word_list		*debug_new_word_list(char *word, size_t index,
					t_token_type type);
t_redirect_list	*debug_new_redirect_list(char *word, size_t index,
					t_redirect_type type);

void			debug_bool_printf_test(bool flag, char *msg);
void			debug_printf_word_list(t_word_list *word_list);
void			debug_free_word_list(t_word_list *word_list);
void			debug_printf_redirect(t_redirect_list *redirect);
void			debug_free_redirect(t_redirect_list *redirect);
#endif
