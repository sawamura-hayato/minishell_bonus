#include "parse.h"
#include <stdio.h>

void	ast_expect(t_token **current_token, char op,t_data *d)
{
	t_token *token;

	token = *current_token;
	if (token->type != WORD || token->word[0] != op)
	{
		ast_syntax_error(d,token);
		return;
	}
	token = token->next;
}
