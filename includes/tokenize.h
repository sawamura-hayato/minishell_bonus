/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/24 22:21:32 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdbool.h>
#include <stddef.h>
#include "library.h"

#include <stdio.h>

#define DEFAULT_CHAR_TYPE (0)
#define IS_SUBSTITUTED (1)
#define IS_SINGLE_QUOTED (2)
#define IS_DOUBLE_QUOTED (3)

typedef enum e_token_type
{
	WORD,
	REDIRECT,
	TK_PIPE,
	TK_LOGICAL_OR,
	TK_LOGICAL_AND,
	TK_OPEN_PARENTHESIS,
	TK_CLOSE_PARENTHESIS
} t_token_type;

typedef enum e_quote
{
	DEFAULT,
	SINGLE_QUOTE_FLAG,
	DOUBLE_QUOTE_FLAG
} t_quote;

typedef struct s_token
{
	const char		*word;
	const char		*type;
	t_token_type	tk_type;
	struct s_token	*next;
} t_token;

// tokenize.c
t_token *tokenize(const char *line);

// get_current_word_size.c
size_t token_get_current_word_size(char *line);
size_t token_get_operator_size(char *line);
size_t token_get_redirect_list_size(char *line);
size_t token_get_special_word_size(char *line);

// get_current_token.c
char *token_get_current_word(char *line, size_t size);
void token_get_current_token(t_token **head, char **line);
char	*token_get_type_word(char *word);

// set_flag.c
t_quote token_set_flag_quote(char quote);
t_token_type token_set_flag_token(char *line);

// linear_linked_token.c
t_token *create_token(char *word, t_token_type token_type);
void token_addback(t_token **head, t_token *new_token);
t_token *token_end(void);
void free_token(t_token *token_list);
void debug_print_token(t_token *token_list);

// library
int ft_isspace(char c);
bool ft_is_special_char(char c);
size_t ft_strlen(const char *str);

void *try_malloc(size_t size);
void *try_calloc(size_t count, size_t size);

#endif
