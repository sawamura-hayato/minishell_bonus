#include "parse.h"

void debug_print_ast_list(t_ast_list *root)
{
	t_ast_list *p;

	p = root;
	while(p)
	{
		debug_print_ast(root->ast);
		p = p->next;
	}
}
