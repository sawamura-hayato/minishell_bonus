/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:44:42 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/06 21:50:32 by tyamauch         ###   ########.fr       */
/* ************************************************************************** */

/*                                                                            */
#include "parse.h"

t_ast *ast_parse(t_token **token_adress, t_data *d) 
{
	t_token *token = *token_adress;
 	t_ast *left_node = ast_command(token,d);
	e_ast_type type;
	if(left_node== NULL	)
		ast_free_all_nodes(left_node);
  	while (true)
  	{
    	if (token != NULL && is_operator(token->type))
		{
			type = token -> type;
			token = token ->next;//operatarのtoken
      		left_node = ast_make_ast_ope(type, left_node, ast_command(token));
	  		token = token ->next;// 
		}
    	else
      		return left_node;
	}
}

t_ast *ast_command(t_token **token,t_data *d) 
{
	t_ast *command_node;
  if (token->word[0] == '(')//怪しい 
  {
    t_ast *node = ast_parse(token);
    expect(token,')');
    return node;
  }
  if (*token == NULL || is_opereter(*token))
		syntax_error(d);//他ではない
  return ast_make_command_list(command_node,token); 
}

t_ast * ast_make_command_list(t_ast *node,t_token **token_adress)
{
	token = *token_adress;

	while(token != NULL && !is_opereter(token -> type) )
	{
		node->command_list->fd = STDOUT_FINENO;
		node->command_list->fd_type = STDOUT;
		node->command_list->pid = -1;
		//tokenの中身を実際に見てリダイレクトがあれば次のトークン
		//とリダレクトリストを作る
		if(is_redirect(token->type))
			ast_make_ridirect_list(&(node -> redirect_list),token);
		else
			ast_make_word_list(&(node -> command_list),token);
		if (!token_next(&token))
			return (NULL);
	}
	return(node);
}

t_ast * ast_make_ast_ope(e_ast_type type,t_ast *left_hand,t_ast *right_hand )
{
	t_ast * ast_ope;

	if(right_hand== NULL)
		return(syntax_error(left_hand,right_hand));//left_hand free
	ast_ope = try_calloc(1,sizeof(t_ast));
	ast_ope -> type = type;
	ast_ope -> command_list = NULL;
	ast_ope -> left_hand = left_hand;
	ast_ope -> right_hand = right_hand;
	return (ast_ope);
}

t_ast *ast_init_node(t_token **token_adress)
{
	t_ast *node;
	node = (t_ast*)malloc(sizeof(t_ast)*1);
	node ->type = command;
	node ->command_list = NULL;// cat infile
	node -> left_hand = NULL;
	node -> right_hand = NULL; 
	return(node); 
}

void ast_add_back_ast_node(t_ast **head, t_ast *new_node)
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

void ast_make_word_list(t_command **command_list, t_token token)
{
	t_command *node;
	node = ast_init_word_word_node(node);
	add_back_word_list(command_list,node);
}

void ast_make_redirect_list(t_redirect **redirect_list, t_token **token_address, t_data *d)
{
	t_token	*token = *token_address;
	t_redirect *node;

	ast_init_redirect_node(node);
	add_back_redirect_list(redirect_list,node);
	token = token -> next;
	if(token == NULL || is_operetor(token))
		syntax_error();
	ast_init_redirect_word_node(node);
	add_back_redirect_list(redirect_list,node);
	token = token -> next;
	if(token == NULL || is_operetor(token))
		syntax_error();
}

//redirectのnode(<)
t_word_list *ast_init_redirect_node(t_redirect *node);
{
	node = try_calloc(1,sizeof(t_redirect));
	//t_redirectとtokenをstrcmpなどで比較する必要がある
	set_redirect_type(token);//redirectタイプをsetする関数
}

t_command *ast_init_word_word_node(t_command *node,t_token *token)
{
	node = try_calloc(1,sizeof(t_word_list));
	node->word = try_strdup(token_>word);
	node->index = token->index;
	node->type = token->type;
	return(node);
}

void add_back_word_list(t_word **head,t_word *node);
{
	;
}

//redirectのnode(word)
t_word ast_init_redirect_word_node(t_redirect *node);
{
	node = try_calloc(1,sizeof(t_redirect));
	set_word(node->word);
	set_redirect_type(token);//redirectタイプをsetする関数
}

void ast_add_back_redirect_list(t_redirect **head,t_redirect *node)
{
	;
}

//token のindexを使う処理に変更するかも
t_token	*ast_token_next(t_token **token_address)
{
	t_token	*token = *token_address->next;
	if (token != NULL && is_quotation_closed(token) == false)
	{
		syntax_error();
		return (NULL);
	}
	return (token);
}

 void * syntax_error(t_ast *left_node,t_ast *right_node)
 {
	*ast_free_all_nodes(t_ast *left_hanf);
	*ast_free_all_nodes(t_ast *right_right);
 }

void	*ast_free_all_nodes(t_ast *node)
{
	if(node != NULL && node-> left_hand != NULL)
		ast_free_all_nodes(node-> left_hand);
	if(node != NULL && node-> right_hand != NULL)
		ast_free_all_nodes(node-> right_hand);
	free(node);
	return (NULL);
}
bool is_opereter(e_ast_type type)
{
	;
}

void ast_expect(t_token **token,char op) {
  if (token->kind != WORD || token->word[0] != op)
    error("'%c'ではありません", op);
  token = token->next;
}
