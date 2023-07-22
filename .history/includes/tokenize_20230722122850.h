/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/22 12:28:50 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdio.h>

typedef enum e_word_type {
	DEFAUT,
	ODD_SINGL_QUOTE,
	ODD_DOBULE_QUOTE
}	t_word_type;

typedef enum e_opereator_type {
	WORD,
	LOGICAL_OR,
	LOGICAL_AND,
	PIPE,
}	t_operator_type;

typedef struct s_word {
	char		*word;
	t_word_type	type;
}	t_word;

typedef struct s_token {
	struct s_word		*word;
	t_operator_type		operator;
	size_t				n_token;
	struct s_token		*next;
}	t_token;

// t_token	*tokenize(const char *line);
// t_tokne	*token_newtoken(t_token **head, const char *line, size_t start, size_t end);// substr使うなら、startとendのindexが必要
// void	token_set_token_type(t_token *token);
// void	token_addback(t_token **head, t_token *new_token);
// void	token_lasttoken(t_token **head);
// // void	token_remove_token(t_token **head, t_token *target);
// void	token_free_all_tokens(t_token **head);
// bool	token_is_meta_char(char c);// tokenの区切り文字
// bool	token_is_space(char c);//space＆tabは飛ばす 例）'     ls  | cat'
// bool	token_is_quotation(char c);

// t_token	*token_newtoken(const char *line, size_t start, size_t end)
// {
// 	t_token *newtoken;

// 	if (start == end && line[i] == '\0')
// 		return (NULL);
// 	newtoken = malloc_x(sizeof(t_token));
// 	newtoken->next = NULL;
// 	newtoken->word = substr_x(line, start, (end - start));
// 	token_set_token_type(newtoken);
// 	return (newtoken);
// }

// t_token	*tokenize(const char *line)
// {
// 	t_token *head;

// 	head = NULL;
// 	size_t	start = 0;
// 	size_t	i = 0;
// 	bool	quotation = false;
// 	char	target;
// 	while (line[i] != '\0')
// 	{
// 		while (token_is_space(line[i]) && line[i] != '\0')
// 			i++;
// 		i = start;
// 		while (!token_is_meta_char(line[i]) && quotation == false && line[i] != '\0')
// 		{
// 			if (token_is_quotation(line[i]) && line[i] == target)
// 			{
// 				if (!quotation)
// 					target = line[i];
// 				quotation = !quotation;
// 			}
// 			i++;
// 		}
// 		t_token *token =  token_newtoken(line, start, i)
// 		token_addback(head, token);
// 	}
// 	return (head);
// }

#endif
