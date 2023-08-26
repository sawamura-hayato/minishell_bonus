#include "parse.h"
#include "library.h"
#include <stdlib.h>
#include <stdio.h>

/* //token のindexを使う処理に変更するかも */
t_token	*token_next(t_token **current_token,t_data *d)
{
	t_token	*token;

	token = *current_token;
	if(token->next== NULL)
		return(NULL);
	token = token->next;
	if (token != NULL && token_is_quotation(token))
	{
		if(token_is_quotation_closed(token) == false)
		{
			ast_syntax_error(d,token);
			return (NULL);
		}
	}
	*current_token = token;
	return (*current_token);
}

bool token_is_quotation(t_token *token)
{
	if(*(token->type) == IS_SINGLE_QUOTED)
		return (true);
	else if(*(token->type) == IS_DOUBLE_QUOTED)
		return (true);
	else
		return(false);
}

bool					token_is_quotation_closed(t_token *token)
{
	if(token->word[0] == '"' || token->word[0] == '\'')
		return(true);
	else
		return(false);
}

bool	token_is_redirect(t_token_type type)
{
	if(type == REDIRECT)
		return(true);
	else
		return(false);
}
