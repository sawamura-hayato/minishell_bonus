#include "parse.h"

/* error */
/* NULLを返して標準入力待ち */
// token_next 書き換え
				||
			&&		command4
		| 		command3
command1 command2

ls|cat
ls | cat


	|
ls		cat

t_ast *ast_parse(t_token **token_adress) 
{
	t_token *token = *token_adress;
 	t_ast *left_node = command(token);
	e_ast_type type;
	if(left_node== NULL	)
		return(NULL);//ASTをfree
  	while (true)
  	{
    	if (token != NULL && is_opereter(token->type))
		{
			type = token -> type;
			token = token ->next;
      		left_node = ast_make_ast_ope(type, left_node, command(token));
	  		token = token ->next; 
		}
    	else
      		return left_node;
	}
}

t_ast *command(t_token **token) 
{
	t_ast *command_node;
  // 次のトークンが"("なら、"(" expr ")"のはず
  if (token->word[0] == '(') 
  {
    t_ast *node = ast_parse(token);
    expect(token,')');
    return node;
  }
  // そうでなければコマンドのはず
  if (*token == NULL || is_opereter(*token))
	syntax_error();
  return ast_make_command_node(token); 
  //expect commandのなかで線形リスト等を作る処理
}

void expect(t_token **token,char op) {
  if (token->kind != WORD || token->word[0] != op)
    error("'%c'ではありません", op);
  token = token->next;
}

t_ast * ast_make_ast_ope(e_ast_type type,t_ast *left_hand,t_ast *right_hand )
{
	t_ast * ast_ope;

	if(right_hand== NULL)
		return(SYNTAX_ERROR(left_hand,right_hand));//left_hand free
	ast_ope = mallocx(sizeof(t_ast)*1);
	ast_ope -> type = type;
	ast_ope -> command_list = NULL;
	ast_ope -> redirect_list = NULL;
	ast_ope -> left_hand = left_hand;
	ast_ope -> right_hand = right_hand;
	return (ast_ope);
}

void make_linked_list(t_ast *node,t_token **token);
{
	token = *token;

	while(token == NULL || is_opereter(token -> type) )
	{
		if(is_redirect(token))
			make_ridirect_list(&(node -> redirect_list),token);
		else
			make_command_list(&(node -> command_list),token);
		// token = token -> next;
		if (!token_next(&token))
			return (NULL);
	}
}

void make_redirect_list(t_redirect redirect_list, t_token **token_address)
{
	t_token	*token = *token_address;
	t_redirect *node;

	
	node = mallocx(sizeof(t_redirect)*1);
	/* type set */
	init_node(node);
	add_back_redirect_list();
	token = token -> next;
	if(token == NULL || is_operetor(token))
		syntax_error();
	node = mallocx(sizeof(t_redirect)*1);
	/* type set */
	init_node(node);
	add_back_redirect_list();
	/* expect(); */ 
	/* 引数チェック */ 
}

void make_command_list(t_command, command_list, t_token token)
{
	t_command *node;
	
	node = mallocx(sizeof(t_command)*1);
	add_back_command_list();
}

t_ast *ast_make_command_node(t_token **token_adress)
{
	t_ast *node;
	node = (t_ast*)malloc(sizeof(t_ast)*1);
	node ->type = command;
	node ->command_list = NULL;// cat infile
	node ->redirect_list = NULL;//<< eof < Makefile
	node -> left_hand = NULL;
	node -> right_hand = NULL; make_linked_list(node,token_adress); return(node); 
	
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

t_token	*token_next(t_token **token_address)
{
	t_token	*token = *token_address->next;
	if (token != NULL && is_quotation_closed(token) == false)
	{
		syntax_error();
		return (NULL);
	}
	return (token);
}
'  a'

// void * SYNTAX_ERROR(t_ast *left_node,t_ast *right_node)
// {
// 	if(left_node != NULL && left_node-> left_hand != NULL)
// 		SYNTAX_ERROR(left_node-> left_hand,NULL);
// 	if(right_node != NULL && right_node-> right_hand != NULL)
// 		SYNTAX_ERROR(right_node-> right_hand,NULL);
// 	free(left_node);
// 	free(right_node);
// }

void	*ast_free_all_nodes(t_ast *node)
{
	if(node != NULL && node-> left_hand != NULL)
		ast_free_all_nodes(node-> left_hand);
	if(node != NULL && node-> right_hand != NULL)
		ast_free_all_nodes(node-> right_hand);
	free(node);
	return (NULL);
}
			|
		|		cmd3
cmd1		cmd2
