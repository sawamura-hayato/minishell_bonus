/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:17 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/28 17:32:01 by tterao           ###   ########.fr       */
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
	char			*word;
	e_token_type	type;
	struct s_token	*next;
}	t_token;


// ls||||cat

// ls
// ||||
// cat

t_token	*tokenize(const char *line);
int		token_newtoken(t_token **head, const char *line, size_t start, size_t end);// substr使うなら、startとendのindexが必要
void	token_set_token_type(t_token *token);
// void	token_set_token_type(t_token **head, t_token *token); tokeninzeで細かくするなら、headも必要
void	token_addback(t_token **head, t_token *new_token);
void	token_lasttoken(t_token **head);
// void	token_remove_token(t_token **head, t_token *target);
void	token_free_all_tokens(t_token **head);
bool	token_is_meta_char(char c);// tokenの区切り文字
bool	token_is_space(char c);//space＆tabは飛ばす 例）'     ls  | cat'

int	token_newtoken(t_token **head, const char *line, size_t start, size_t end)
{
	t_token *newtoken;

	if (start == end && line[i] == '\0')
		return (1);
	newtoken = malloc_x(sizeof(t_token));
	newtoken->next = NULL;
	newtoken->word = substr_x(line, start, (end - start));
	token_set_token_type(token);
	token_addback(head, token);
	return (0);
}

t_token	*tokenize(const char *line)
{
	t_token *head;

	head = NULL;
	size_t	start = 0;
	size_t	i = 0;
	while (line[i] != '\0')
	{
		while (token_is_space(line[i]))
			i++;
		i = start;
		while (!token_is_meta_char(line[i]))
			i++;
		if (token_newtoken(&head, line, start, i))
			break ;
	}
	return (head);
}


#endif
