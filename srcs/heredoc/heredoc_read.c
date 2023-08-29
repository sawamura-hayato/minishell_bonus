/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:48:59 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/29 11:17:55 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#define HEREDOC_PROMPT "> "

static void	all_free(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
}

char	*heredoc_read(t_data *d)
{
	char	buff[BUFFER_SIZE + 1];
	char	*line;
	ssize_t	read_bytes;

	line = NULL;
	try_write(STDERR_FILENO, "> ", ft_strlen(HEREDOC_PROMPT), d);
	read_bytes = BUFFER_SIZE + 1;
	while (read_bytes > BUFFER_SIZE)
	{
		read_bytes = read(STDIN_FILENO, buff, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
			return (NULL);
		buff[read_bytes] = '\0';
		if (line == NULL)
			line = try_strdup(buff);
		else
			line = try_strjoin_free(line, buff);
	}
	return (line);
}

static void	heredoc_put_warning(const char *delimiter, t_data *d)
{
	char	*msg;

	msg = try_strjoin("warning: here-document delimited by end-of-file (wanted `", delimiter);
	msg = try_strjoin_free(msg, "')\n");
	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	free(msg);
}

bool	heredoc_read_loop(t_redirect_list *delimiter, t_data *d)
{
	char		*str;
	char		*buff;
	const char	*delimiter_nl = try_strjoin(delimiter->word, "\n");

	str = try_strdup("");
	while (true)
	{
		buff = heredoc_read(d);
		if (buff == NULL && g_signal_num != 0)
		{
			all_free(buff, delimiter->word, (char *)delimiter_nl);
			delimiter->word = str;
			return (false);
		}
		if (buff == NULL || ft_strcmp(buff, delimiter_nl) == 0)
		{
			if (buff == NULL)
				heredoc_put_warning(delimiter->word, d);
			all_free(buff, delimiter->word, (char *)delimiter_nl);
			delimiter->word = str;
			break ;
		}
		str = try_strjoin_free(str, buff);
	}
	return (true);
}
