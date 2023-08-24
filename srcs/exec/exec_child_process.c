/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:48:29 by tterao            #+#    #+#             */
/*   Updated: 2023/08/24 16:50:31 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_command.h"
#include <stdlib.h>

size_t	exec_get_size_arr_word_list(t_word_list *word_list)
{
	size_t	size;
	size_t	index;

	size = 1;
	index = word_list->index;
	while (true)
	{
		word_list = word_list->next;
		if (word_list == NULL)
			break ;
		if (index != word_list->index)
		{
			index = word_list->index;
			size++;
		}
	}
	return (size);
}

char	*exec_get_word_index(t_word_list **word_list)
{
	char	*word;
	size_t	index;

	index = (*word_list)->index;
	word = try_strdup((*word_list)->word);
	(*word_list) = (*word_list)->next;
	while ((*word_list) != NULL && index == (*word_list)->index)
	{
		word = try_strjoin_free(word, (*word_list)->word);
		(*word_list) = (*word_list)->next;
	}
	return (word);
}

char	**exec_change_word_list_to_double_arr(t_word_list *word_list)
{
	char	**arr;
	size_t	index;
	size_t	size;

	size = exec_get_size_arr_word_list(word_list);
	// if (size == 0)
	// 	return (NULL);
	arr = try_malloc((size + 1) * sizeof(char *));
	arr[size] = NULL;
	index = 0;
	while (index < size)
	{
		arr[index] = exec_get_word_index(&word_list);
		index++;
	}
	return (arr);
}

void	exec_child_process(t_ast *node, int *pipefd, t_data *d)
{
	char	**argv;
	char	*filepath;
	int	fd;

	(void)pipefd;
	fd = node->command_list->fd;
	if (fd != STDOUT_FILENO)
	{
		try_dup2(fd, STDOUT_FILENO, 0);
		try_close(fd, d);
	}
	if (node->command_list->word_list != NULL)
	{
		argv = exec_change_word_list_to_double_arr(node->command_list->word_list);
		filepath = exec_make_filepath(node, d);
		char **tmp = argv;
		// while (*tmp)
		// {
			// printf("argv=%s\n", *tmp);
		// 	tmp++;
		// }
		// printf("path=%s\n", filepath);
		execve(filepath, argv, envs_make_envp(d->envs_hashmap));
		// execve(NULL, NULL, envs_make_envp(d->envs_hashmap));
	}
	exit(1);
}