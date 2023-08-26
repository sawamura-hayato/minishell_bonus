/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:27:57 by tterao            #+#    #+#             */
/*   Updated: 2023/08/26 22:52:44 by tterao           ###   ########.fr       */
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

	i = 0;
	while (true)
	{
		file = try_itoa(i);
		file = try_strjoin_free(file, "_thtshell_tmp.txt");
		if (access(file, F_OK) != 0)
			break ;
		free(file);
		i++;
		printf("%d\n", i);
	}
	return (file);
}

static void	heredoc_put_error(t_data *d, bool *is_success)
{
	const char	*msg = "heredoc: string error\n";

	try_write(STDERR_FILENO, msg, ft_strlen(msg), d);
	*is_success = false;
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
	while (w_len >= WRITE_BYTES && i != SIZE_T_MAX)
	{
		printf("word len%zu\n", word_len);
		if (word_len >= (WRITE_BYTES * i))
			w_len = WRITE_BYTES;
		else
			w_len = word_len - (WRITE_BYTES * (i - 1));
		printf("w_len%zu\n\n", word_len);
		w_bytes = try_write(fd, &(node->word[(i - 1) * WRITE_BYTES]), w_len, d);
		if (w_bytes == -1 || i == SIZE_T_MAX)
			heredoc_put_error(d, &is_success);
		i++;
		// printf("%zu\n", i);
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

	// printf("heredoc\n");
	file = get_heredoc_tmpfile();
	// printf("heredoc\n");
	fd = try_open(open(file, O_CREAT | O_RDWR, 0644), file, d);
	if (fd == -1)
	{
		free(file);
		return (NULL);
	}
	// printf("heredoc\n");
	// heredoc_success = write_loop(node, fd, d);
	// --------------------------
	try_write(fd, node->word, ft_strlen(node->word), d);
	try_dup2(fd, STDIN_FILENO, d);
	try_close(fd, d);
	// --------------------------

	unlink(file);
	free(file);
	// if (!heredoc_success)
	// 	return (NULL);
	return (node);
}
