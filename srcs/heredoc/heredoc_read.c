/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:59 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/29 14:05:25 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <readline/readline.h>
#include <readline/history.h>
#define HEREDOC_PROMPT "> "

static void	all_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

// char	*heredoc_read(t_data *d)
// {
// 	char	buff[BUFFER_SIZE + 1];
// 	char	*line;
// 	ssize_t	read_bytes;

// 	line = NULL;
// 	try_write(STDERR_FILENO, "> ", ft_strlen(HEREDOC_PROMPT), d);
// 	read_bytes = BUFFER_SIZE + 1;
// 	while (read_bytes > BUFFER_SIZE)
// 	{
// 		read_bytes = read(STDIN_FILENO, buff, BUFFER_SIZE);
// 		if (read_bytes == -1 || read_bytes == 0)
// 			return (NULL);
// 		buff[read_bytes] = '\0';
// 		if (line == NULL)
// 			line = try_strdup(buff);
// 		else
// 			line = try_strjoin_free(line, buff);
// 	}
// 	return (line);
// }

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
			all_free(buff, delimiter->word);
			delimiter->word = str;
			return (false);
		}
		if (buff == NULL || ft_strcmp(buff, delimiter->word) == 0)
		{
			heredoc_put_warning(buff, delimiter->word, d);
			all_free(buff, delimiter->word);
			delimiter->word = set_heredoc_string(str, is_start);
			break ;
		}
		str = join_heredoc_string(buff, str, &is_start);
	}
	return (true);
}
