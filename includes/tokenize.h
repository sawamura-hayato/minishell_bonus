/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/02 12:08:36 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

# include <stdbool.h>
 #include <stddef.h>
 
typedef enum e_word_type {
	SINGL_QUOTE,
	DOBULE_QUOTE
}	t_word_type;

typedef enum e_opereator_type {
	WORD,
	LOGICAL_OR,
	LOGICAL_AND,
	PIPE,
}	t_operator_type;

typedef enum e_quote {
	DEFAULT,
	SINGLE_QUOTE_FLAG,
	DOUBLE_QUOTE_FLAG
}	t_quote;

typedef struct s_token {
	char				*word;
	t_operator_type		operator;
	size_t				index;
	struct s_token		*next;
}	t_token;


t_token	*init_token(size_t index);
t_token	*create_token(char *word, t_operator_type operator, size_t index);
void	debug_print_token(t_token *token_list);
t_token	*tokenize(const char *line);

bool	token_can_get_quote_token(t_token **token, const char **prompt, \
										t_quote *f_quote, size_t index);
#endif
