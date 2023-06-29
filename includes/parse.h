/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/29 21:29:28 by tyamauch         ###   ########.fr       */
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
	t_command		*command_list;// cat infile
	t_redirect		*redirect_list;//<< eof < Makefile
	struct s_ast	*left_hand;
	struct s_ast	*right_hand;
}	t_ast;


t_ast *ast_parse(t_token *token);
{
	t_command *command_list;
	t_redirect *redirect_list;
	t_ast *ast_parse;
 		
	command_list = ast_make_command_list(token);
	redirect_list = ast_make_redirect_list(token);
	ast_parse = ast_make_ast(type, command_list,redirect_list,left_hand, right_hand);
	return(ast_parse);
}

//コマンドリスト関連
static t_command	*ast_make_command_list(t_token *token);
{
	ast_init_command_node(*word);
	ast_add_command_node(**head,*new_token);
}

t_ast *init_command_node(char *word)
{
	t_ast *node;
	node = (t_ast*)malloc(sizeof(t_ast)*1);
	if(node == NULL)
		ft_put_error();
	node ->type;
	node ->command_list = NULL;// cat infile
	node ->redirect_list = NULL;//<< eof < Makefile
	node -> left_hand = NULL;
	node -> right_hand = NULL;
	return(node);
}

void ast_add_command_node(t_ast **head, t_ast *new_node)
{
	t_ast *node;
	node = *head;

	while(node != NULL)
	{
		if(node -> next == NULL)
			break;
		node = node-> next;
	}
	if(node != NULL)
	{
		node-> next = new_node;

		new_node -> next = NULL;
		new_node -> prev = node;
	}
	else
	{
		new_node -> next = NULL;
		new_node -> prev = NULL;
		*head = new_node;
	}
}
static t_command *ast_init_command_node(char* *word);
static void *ast_add_command_node(t_command **head,t_command *new_token);

//redirect関連
static t_redirect	*ast_make_redirect_list(t_token *token);
static t_redirect *ast_init_redirect_node(char *word,e_redirect_type,type);
static void *ast_add_redirect_node(t_redirect **head,t_redirect *new_token);

//ast関連
static t_ast		*ast_make_ast(e_ast_type type, t_ast *left_hand, t_ast *right_hand);
static t_ast *ast_init_ast_node(e_ast_type type,);
static t_ast		*ast_add_ast_node(t_ast **head,t_ast *new_token);

//
t_ast *operetor(t_token **head) 
{
	t_token *token = *head;
  t_ast *node = command();

  while (token)
  {
    if (consume(&token,PIPE))
      node = new_node_operetor(ND_PIPE, node, command());
    else if (consume(&token,LOGICAL_AND))
      node = new_node_operetor(ND_AND, node, command());
    else if (consume(&token,LOGICAL_OR))
      node = new_node_operetor(ND_OR, node, command());
    else
      return node;
  }
}

t_ast *command(t_token **token) 
{
  // 次のトークンが"("なら、"(" expr ")"のはず
  if (consume('(')) 
  {
    t_ast *node = expr();
    expect(')');
    return node;
  }
  else if()
  // そうでなければコマンドのはず
  return new_node_command(ast_make_command_list(*token));
  //expect commandのなかで線形リスト等を作る処理
}


#endif
