/* ************************************************************************** */
/*                                                                            */

/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:35:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/06 13:35:43 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "parse.h"
#include "exec_command.h"
#include "heredoc.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static void	add_line_history(char *line)
{
	if (line[0] == NULL_CHAR)
		return ;
	add_history(line);
}

static bool	is_only_spaces(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

static char	*read_line()
{
	char	*line;

	line = readline(PROMPT);
	if (line == NULL || is_only_spaces(line))
	{
		free(line);
		return (NULL);
	}
	add_line_history(line);
	return (line);
}

void	read_eval_print_loop()
{
	char	*line;
	t_token *token;
	t_ast *pasre_node;
	t_data d;

	extern const char	**environ;

	envs_init(environ, &d);
	d.syntax_flag = false;
	while (true)
	{
		int fd  = dup(STDIN_FILENO);
		line = read_line();
		if (line == NULL)
			continue ;
		token = tokenize(line);
		// debug_print_token(token);
		pasre_node = parse(&token,&d);
		debug_print_ast(pasre_node);
		heredoc(pasre_node, &d);
		free(line);
		try_dup2(fd, STDIN_FILENO, &d);
		try_close(fd, &d);
	}
}
