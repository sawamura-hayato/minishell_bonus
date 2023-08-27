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

void	reset_vars(t_data *d);
void	end_command(char *line, t_data *d);

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
		return (NULL);
	add_line_history(line);
	return (line);
}

void	read_eval_print_loop()
{
	char	*line;
	t_token *token;
	t_ast 	*ast;
	t_data	d;
	extern const char	**environ;

	envs_init(environ, &d);
	while (true)
	{
		reset_vars(&d);
		line = read_line();
		if (line == NULL)
		{
			end_command(line, &d);
			continue ;
		}
		token = tokenize(line);
		// debug_print_token(token);
		ast = parse(&token,&d);
		// debug_print_ast(ast);
		heredoc(ast, &d);
		exec_command(ast, EXEC_START, &d);
		end_command(line, &d);
	}
}
