/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/13 19:57:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdbool.h>
#include <stddef.h>

typedef enum e_token_type
{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	REDIRECT,
	TOKEN_PIPE,
	TOKEN_LOGICAL_OR,
	TOKEN_LOGICAL_AND,
} t_token_type;

typedef enum e_quote
{
	DEFAULT,
	SINGLE_QUOTE_FLAG,
	DOUBLE_QUOTE_FLAG
} t_quote;

typedef struct s_token
{
	char *word;
	t_token_type type;
	size_t index;
	struct s_token *next;
} t_token;

// tokenize.c
t_token *tokenize(const char *line);

// get_next_token_index.c
size_t token_can_get_next_token_index(t_token *head,
									  char **line, t_quote f_quote, size_t index);
bool token_is_a_control_char(t_token_type token_type);
t_token_type token_get_last_token_type(t_token *head);

// get_quote_token.c
bool token_can_get_quote_token(t_token **token, char **line,
							   t_quote *f_quote, size_t index);

// get_current_word_size.c
size_t	token_get_current_word_size(char *line, t_quote f_quote);
size_t	token_get_operator_size(char *line);
size_t	token_get_redirect_size(char *line);
size_t	token_get_special_word_size(char *line);

// get_current_token.c
size_t token_get_current_word_size(char *line, t_quote f_quote);
char *token_get_current_word(char *line, size_t size);
void token_get_current_token(t_token **head, char **line, t_quote f_quote, size_t *index);

// set_flag.c
t_quote token_set_flag_quote(char quote);
t_token_type token_set_flag_token(char *line, t_quote f_flag);

// linear_linked_token.c
t_token *create_token(char *word, t_token_type token_type, size_t index);
void token_addback(t_token **head, t_token *new_token);
t_token *token_end(void);
void free_token(t_token *token_list);
void debug_print_token(t_token *token_list);

// library
int		ft_isspace(char c);
bool	ft_is_special_char(char c);
size_t	ft_strlen(const char *str);

void	*try_malloc(size_t size);
void	*try_calloc(size_t count, size_t size);

#endif
