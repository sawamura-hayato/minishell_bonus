#include "parse.h"

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
	if((*(token->type) == IS_SINGLE_QUOTED)
		|| (*(token->type) == IS_DOUBLE_QUOTED))
		return (true);
	else
		return(false);
}

bool	token_is_quotation_closed(t_token *token)
{
	size_t i;
	size_t single_q_count;
	size_t double_q_count;
	char *s;

	i = 0;
	single_q_count = 0;
	double_q_count = 0;
	s = (char*)token->type;
	while(s[i])
	{
		if(token->type[i] == (IS_SINGLE_QUOTED + '0'))
			single_q_count++;
		if(token->type[i] == (IS_DOUBLE_QUOTED + '0'))
			double_q_count++;
		i++;
	}
	if((single_q_count %2) == 0 && (double_q_count %2) == 0)
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
