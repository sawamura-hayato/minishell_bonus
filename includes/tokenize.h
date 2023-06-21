/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/21 20:04:55 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

enum e_token_type {
	WORD,
	LOGICAL_OR,
	LOGICAL_AND,
	PIPE,
};

typedef struct s_token {
	char			*token;//wordの方がbetter?
	e_token_type	type;
	struct s_token	*next;
}	t_token;


// ls||||cat

// ls
// ||||
// cat

t_token	*token_newtoken(t_token **head);
void	token_set_token_type(t_token *token);
void	token_addback(t_token **head, t_token *new_token);
bool	token_is_meta_char(char c);

#endif
