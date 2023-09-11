/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:59 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/11 16:13:59 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <readline/readline.h>
#include <readline/history.h>
#define HEREDOC_PROMPT "> "

static void	heredoc_put_warning(char *buff, const char *delimiter, t_data *d)
{
	char	*msg;

	if (buff != NULL)
		return ;
	msg = try_strjoin(
			"warning: here-document delimited by end-of-file (wanted `",
			delimiter);
	msg = try_strjoin_free(msg, "')\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
}

static char	*set_heredoc_string(char *str, bool is_start)
{
	if (is_start)
		return (str);
	else
		return (try_strjoin_free(str, "\n"));
}

static char	*join_heredoc_string(char *buff, char *str, bool *is_start)
{
	if (*is_start)
	{
		*is_start = false;
		free(str);
		return (buff);
	}
	str = try_strjoin_free(str, "\n");
	str = try_strjoin_free(str, buff);
	free(buff);
	return (str);
}

static void	get_delimiter_word_and_type(t_redirect_list *delimiter, \
										char *str, bool is_start)
{
	char	*type;

	type = delimiter->type;
	delimiter->word = set_heredoc_string(str, is_start);
	delimiter->type = token_get_all_expand_type_word(delimiter->word);
	free(type);
}

bool	heredoc_read_loop(t_redirect_list *delimiter, t_data *d)
{
	char	*str;
	char	*buff;
	bool	is_start;

	is_start = true;
	str = try_strdup("");
	while (true)
	{
		buff = readline(HEREDOC_PROMPT);
		if (buff == NULL && g_signal_num != 0)
		{
			heredoc_all_free(buff, delimiter->word);
			delimiter->word = str;
			return (false);
		}
		if (buff == NULL || ft_strcmp(buff, delimiter->word) == 0)
		{
			heredoc_put_warning(buff, delimiter->word, d);
			heredoc_all_free(buff, delimiter->word);
			get_delimiter_word_and_type(delimiter, str, is_start);
			break ;
		}
		str = join_heredoc_string(buff, str, &is_start);
	}
	return (true);
}
