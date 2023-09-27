/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:27:57 by tterao            #+#    #+#             */
/*   Updated: 2023/09/26 18:48:31 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "exec_command.h"
#include "library.h"
#define WRITE_BYTES 2000

void	*exec_delete_file_free(char *file, t_data *d);

static char	*get_heredoc_tmpfile(void)
{
	char	*file;
	char	*tmp;
	int		i;

	i = 0;
	while (true)
	{
		file = try_itoa(i);
		tmp = file;
		file = try_strjoin("/tmp/thtshell_tmp", file);
		free(tmp);
		if (access(file, F_OK) != 0)
			break ;
		free(file);
		i++;
		if (i == 0)
			return (NULL);
	}
	return (file);
}

static void	heredoc_put_error(t_data *d)
{
	const char	*msg = "heredoc: string error\n";

	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
}

static bool	write_loop(t_redirect_list *node, int fd, t_data *d)
{
	ssize_t			w_bytes;
	size_t			i;
	bool			is_success;
	ssize_t			w_len;
	const size_t	word_len = ft_strlen(node->word);

	is_success = true;
	w_len = WRITE_BYTES;
	i = 1;
	while (w_len == WRITE_BYTES && i != SIZE_MAX)
	{
		if (word_len >= (WRITE_BYTES * i))
			w_len = WRITE_BYTES;
		else
			w_len = word_len - (WRITE_BYTES * (i - 1));
		w_bytes = try_write(fd, &(node->word[(i - 1) * WRITE_BYTES]), w_len, d);
		if (w_bytes == -1 || i == SIZE_MAX)
			heredoc_put_error(d);
		i++;
	}
	try_close(fd, d);
	return (is_success);
}

static bool	set_heredoc_string_to_stdin(char *file, t_data *d)
{
	int	fd;

	fd = try_open(open(file, O_RDONLY), file, d);
	if (fd == -1)
	{
		exec_delete_file_free(file, d);
		return (false);
	}
	try_dup2(fd, STDIN_FILENO, d);
	try_close(fd, d);
	exec_delete_file_free(file, d);
	return (true);
}

t_redirect_list	*exec_redirect_heredoc(t_redirect_list *node, t_data *d)
{
	char	*file;
	int		fd;

	file = get_heredoc_tmpfile();
	if (file == NULL)
	{
		heredoc_put_error(d);
		return (NULL);
	}
	fd = try_open(open(file, O_CREAT | O_RDWR, 0644), file, d);
	if (fd == -1)
	{
		free(file);
		return (NULL);
	}
	if (write_loop(node, fd, d) == false)
		return (exec_delete_file_free(file, d));
	if (set_heredoc_string_to_stdin(file, d))
		return (node);
	else
		return (NULL);
}
