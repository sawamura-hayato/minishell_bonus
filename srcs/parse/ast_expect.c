/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:51:18 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/09 20:37:42 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ast_list_expect(t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (token == NULL || token->tk_type != TK_LOGICAL_OR
			|| token->tk_type != TK_LOGICAL_AND)
	{
		ast_syntax_error(d, token);
		return ;
	}
}

void	ast_expect(t_token_type expecting_type,
					t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (token == NULL || token->tk_type != expecting_type)
	{
		ast_syntax_error(d, token);
		return ;
	}
}

void	ast_expect_word(t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (token == NULL
		|| (token->tk_type != WORD && token->tk_type != REDIRECT))
	{
		ast_syntax_error(d, token);
		return ;
	}
}
