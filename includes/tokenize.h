/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/15 20:29:58 by tterao           ###   ########.fr       */
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

t_token	*token_newtoken();
t_token	*token_addback();

#endif
