#include "parse.h"

t_ast	*ast_operator_node(t_ast_node_type type, t_ast *left_hand, t_ast *right_hand, t_data *d)
{
	t_ast	*ast_operator_node;

	if (right_hand == NULL)
	{
		ast_syntax_error(d,NULL);
		return (NULL); 
	}
	ast_operator_node = ast_init_node();
	ast_operator_node->type = type;
	ast_operator_node->left_hand = left_hand;
	ast_operator_node->right_hand = right_hand;
	return (ast_operator_node);
}

bool	ast_is_opereter(t_token_type type)
{
	if(type == TK_LOGICAL_OR || type == TK_LOGICAL_AND || type == TK_PIPE)
		return(true);
	else
		return(false);
}
