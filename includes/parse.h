/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/30 22:25:48 by tyamauch         ###   ########.fr       */
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
//コマンドリスト関連
	
void make_linked_list(t_ast *node,t_token **token);
{
	token = *token;

	while(token == NULL || is_opereter(token -> type) )
	{
		if(is_redirect(token))
			make_ridirect_list(&(node -> redirect_list),token);
		else
			make_command_list(&(node -> command_list),token);
	}
}

make_redirect_list(t_redirect redirect_list, t_token token)
{
	t_redirect *node;
	
	node = mallocx(sizeof(t_redirect)*1);
	add_back_redirect_list();
	//expect();
}

make_command_list(t_command, command_list, t_token token)
{
	t_command *node;
	
	node = mallocx(sizeof(t_command)*1);
	add_back_command_list();
}

t_ast *ast_make_ast_comand(t_token **token_adress)
{
	t_ast *node;
	node = (t_ast*)malloc(sizeof(t_ast)*1);
	if(node == NULL)
		ft_put_error();
	node ->type = command;
	node ->command_list = NULL;// cat infile
	node ->redirect_list = NULL;//<< eof < Makefile
	node -> left_hand = NULL;
	node -> right_hand = NULL;
	make_linked_list(node,token_adress);
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

t_ast * ast_make_ast_ope(e_ast_type type,t_ast *left_hand,t_ast *right_hand )
{
	t_ast * ast_ope;

	ast_ope = mallocx(sizeof(t_ast)*1);
	ast_ope -> type = type;
	ast_ope -> command_list = NULL;
	ast_ope -> redirect_list = NULL;
	ast_ope -> left_hand = left_hand;
	ast_ope -> right_hand = right_hand;
	return (ast_ope);
}

t_ast *ast_parse(t_token **token_adress) 
{
	t_token *token = *token_adress;
 	t_ast *node = command(token);
 	t_ast *new_node ;

  while (token)
  {
    if ((token->type) == PIPE)
      new_node = ast_make_ast_ope(PIPE, node, command(token->next));
    else if ((token -> type) == LOGICAL_AND)
      new_node = ast_make_ast_ope(LOGICAL_AND, node, command(token->next));
    else if ((token -> type) == LOGICAL_OR)
      new_node = ast_make_ast_ope(LOGICAL_OR, node, command(token->next));
    else
      return node;
  }
}

void expect(t_token **token,char op) {
  if (token->kind != WORD || token->word[0] != op)
    error("'%c'ではありません", op);
  token = token->next;
}

t_ast *command(t_token **token) 
{
	t_ast *command_node;
  // 次のトークンが"("なら、"(" expr ")"のはず
  if (token->word[0] == '(') 
  {
    t_ast *node = ast(token);
    expect(token,')');
    return node;
  }
  // そうでなければコマンドのはず

  command_node = ast_make_ast_command(token); 
  return command_node;
  //expect commandのなかで線形リスト等を作る処理
}


#endif
