/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:23 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/13 18:52:40 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "parse.h"
#include "init.h"
#include <stdlib.h>

//expansion.c
void	expansion(t_ast *node, t_data **d);

//expand_variable.c
void	expand_variable(t_ast *node, t_data *d);
char	*expand_convert_doller_word(char **word, t_data *d);
char	*expand_get_expanded_token_word(char *token_word, t_data *d);
void	expand_token_word_list(t_word_list *token, t_data *d);
void	expand_token_redirect_list(t_redirect *token, t_data *d);
void	expand_variable_word_list(t_word_list *head, t_data *d);
void	expand_variable_redirect_list(t_redirect *head, t_data *d);

//expand_word_splitting.c
void	expand_word_splitting(t_ast *node);//IFSを確認 クオテーションで囲まれていない && スペースがある場合、線形リストのトークンを分割
char	*expand_get_splitting_word(char **word)
void	expand_get_splitting_word_list(t_word_list **word_list)
void	expand_splitting_word_list(t_word_list *word_list, t_envs *ifs)
void	expand_splitting_redirect_list(t_redirect *redirect_list, t_envs *ifs)
void	expand_word_splitting(t_ast *node, t_data *d)

// expand_filename.c
void	expand_filename(t_ast *node);
void	expand_filename_word_list(t_word_list *word_list);
void	expand_filename_redirect_list(t_redirect redirect_list);
bool	expand_is_wildcard(char *word);
bool	expand_is_filename_word(char *word, char *target);
void	word_list_insert_target(t_word_list *word_list, char *taget);
bool	expand_is_filename_word(char *word, char *target);
size_t	expand_filename_word_list_size(t_word_list *word_list);
void	expand_can_get_filename_word_list(t_word_list *word_list);

//expand_delete_quote.c
void	expand_delete_quotation(t_ast *node);
void	word_list_delete_target_type(t_word_list *word_list, t_token_type taget);
void	redirect_list_delete_target_type(t_word_list *word_list, t_token_type taget);
void	expandion_delete_quotation_word_list(t_word_list *word_list);
void	expandion_delete_quotation_redirect_list(t_redirect *redirect_list);

#endif
