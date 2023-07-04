include "parse.h"

/* error */
/* NULLを返して標準入力待ち */

void make_linked_list(t_ast *node,t_token **token);
{
	token = *token;

	while(token == NULL || is_opereter(token -> type) )
	{
		if(is_redirect(token))
			make_ridirect_list(&(node -> redirect_list),token);
		else
			make_command_list(&(node -> command_list),token);
		token = token -> next;
	}
}

void make_redirect_list(t_redirect redirect_list, t_token token)
{
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
 	t_ast *left_node = command(token);
	if(left_node== NULL	)
		return(SYNTAX_ERROR());//ASTをfree
 	t_ast *opereter ;

  while (token)
  {
    if (is_opereter(token->type))
	{
 		t_ast *right_node = command(token);
		if(right_node== NULL	)
			SYNTAX_ERROR;
      opereter = ast_make_ast_ope(token -> type, node, right_node);
	  token = token ->next; 
	}
    /* else if ((token -> type) == LOGICAL_AND) */
    /*   new_node = ast_make_ast_ope(LOGICAL_AND, node, command(token->next)); */
    /* else if ((token -> type) == LOGICAL_OR) */
      /* new_node = ast_make_ast_ope(LOGICAL_OR, node, command(token->next)); */
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
