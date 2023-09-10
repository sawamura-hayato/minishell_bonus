/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:35:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/09 18:50:56 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenize.h"
#include "parse.h"
#include "heredoc.h"
#include "expansion.h"
#include "exec_command.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	reset_vars(t_data *d);
void	end_command(char *line, t_data *d);
void	eof(t_data *d);
void	set_signal_readline(t_data *d);
void	get_signal_num(t_data *d);
void	ignore_signal(t_data *d);

int	g_signal_num = 0;

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

static char	*_readline(t_data *d)
{
	char	*line;

	reset_vars(d);
	set_signal_readline(d);
	line = readline(PROMPT);
	ignore_signal(d);
	get_signal_num(d);
	if (line == NULL)
		eof(d);
	if (is_only_spaces(line))
	{
		free(line);
		return (NULL);
	}
	add_history(line);
	return (line);
}

static void	free_all_data(t_token *token, t_ast *ast)
{
	token_free_all_tokens(token);
	if (ast != NULL)
		ast_free_all_nodes(ast);
}

void	read_eval_print_loop(t_data *d)
{
	char	*line;
	t_token	*token;
	t_ast_list	*ast_list;

	rl_outstream = stderr;
	while (true)
	{
		line = _readline(d);
		if (line == NULL)
		{
			end_command(line, d);
			continue ;
		}
		token = tokenize(line);
		ast_list = parse(&token, d);
		debug_print_ast_list(ast_list);
		/* if (d->syntax_flag == false && heredoc(ast, d)) */
		/* { */
		/* 	expansion(ast, d); */
		/* 	exec_command(ast, EXEC_START, d); */
		/* } */
		/* free_all_data(token, ast); */
		end_command(line, d);
	}
}
