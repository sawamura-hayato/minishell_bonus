/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/29 17:34:07 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

enum e_redirect_type
{
	REDIRECTING_INPUT, // <
	REDIRECTING_OUTPUT,// >
	APPENDING_OUTPUT,// >>
	FILE,// redirect file
	HERE_DOCUMENTS, // <<
	DELIMITER, // << delimitter
};

enum e_ast_type
{
	PIPE,
	LOGICAL_AND,
	LOGICAL_OR,
	COMMAND,
};

typedef struct s_command
{
	char				*word;
	// char				*expanded_word;
	struct s_command	*next;
}	t_command;

typedef struct s_redirect
{
	char				*word;
	struct s_redirect	*next;
	e_redirect_type		type;
}	t_redirect;

typedef struct s_ast
{
	e_ast_type		type;
	t_command		*command_list;// cat infile echo a
	t_redirect		*redirect_list;
	struct s_ast	*left_hand;
	struct s_ast	*right_hand;
	int				fd;
	pid_t			pid;
}	t_ast;


typedef struct s_ast
{
	e_ast_type		type;
	// ↓tokenを並び替えるデータ構造にする
	t_token			*command_list;// cat infile
	t_token			*input_redirect_list;//<< eof < Makefile
	t_token			*output_redirect_list;// > out >> apend
	struct s_ast	*left_hand;
	struct s_ast	*right_hand;
}	t_ast;


ls infile << eof <Makefile > out >> apend a b | ls

ls infile a b
<< eof <Makefile > out >> apend


cat
infiile
|
ls

------------------------

cmd1 | cmd2 || cmd3 | cmd4

				|
			||		cmd4
		|		cmd3
	cmd1	cmd2
------------------------

cmd1 | (cmd2 || cmd3) | cmd4

		|
	cmd1	|
		||	   cmd4
	cmd2  cmd3
------------------------

------------------------
(a || b) && ls

		&&
	||		ls
a		b
------------------------


					|
				|		command4
		  |			comamnd3
command1	command2


		  |			comamnd3
command1	command2


		  |
command1	command2



		  |
command1	command2
					comamnd3
						command4

t_ast		*ast_new_node_ope(e_ast_type type, t_ast *left_hand, t_ast *right_hand);
t_ast		*ast_new_node_command(t_command *command, t_redirect *redirect);
t_command	*ast_make_command_list(t_token *token);
t_command	*ast_make_redirect_list(t_token *token);
#endif
