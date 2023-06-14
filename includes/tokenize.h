/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/14 17:01:07 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

enum e_token_type {
	WORD,
	LOGICAL_OR,
	LOGICAL_AND,
	PIPE
}

typedef struct s_token {
	char			*token;
	e_token_type	type;
	struct	s_token	*next;
}	t_token;

// ls||||cat

// ls
// ||||
// cat

t_token	*new_token();


#endif