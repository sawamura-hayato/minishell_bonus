/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:27:57 by tterao            #+#    #+#             */
/*   Updated: 2023/08/26 21:51:56 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "exec_command.h"
#include "library.h"
#define WRITE_BYTES 2000

static char	*get_heredoc_tmpfile(void)
{
	char		*file;
	int			i;
	struct stat	sb;

	i = 0;
	while (true)
	{
		file = try_itoa(i);
		file = try_strjoin_free(file, "_thtshell_tmp.txt");
		if (stat(file, &sb) != -1)
			continue ;
		if (!S_ISREG(sb.st_mode) && access(file, F_OK) != 0)
			break ;
		free(file);
		i++;
	}
	return (file);
}

static bool	write_loop(t_redirect_list *node, int fd, t_data *d)
{
	ssize_t		w_bytes;
	size_t		i;
	const char	*msg = "heredoc: string error\n";
	bool		is_success;

	is_success = true;
	w_bytes = WRITE_BYTES;
	i = 0;
	while (w_bytes == WRITE_BYTES)
	{
		w_bytes = try_write(fd, &(node->word[i * WRITE_BYTES]), WRITE_BYTES, d);
		if (w_bytes == -1 || i == SIZE_T_MAX)
		{
			try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
			is_success = false;
			break ;
		}
		i++;
	}
	try_dup2(fd, STDIN_FILENO, d);
	try_close(fd, d);
	return (is_success);
}

t_redirect_list	*exec_redirect_heredoc(t_redirect_list *node, t_data *d)
{
	char	*file;
	int		fd;
	bool	heredoc_success;

	file = get_heredoc_tmpfile();
	fd = try_open(open(file, O_CREAT | O_RDWR, 0644), file, d);
	if (fd == -1)
	{
		free(file);
		return (NULL);
	}
	heredoc_success = write_loop(node, fd, d);
	unlink(file);
	free(file);
	if (!heredoc_success)
		return (NULL);
	return (node);
}
