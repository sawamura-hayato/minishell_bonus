/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:51:18 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/06 19:37:50 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ast_expect(t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (!d->syntax_flag && (token == NULL || token->tk_type != TK_CLOSE_PARENTHESIS))
	{
		ast_syntax_error(d, token);
		return ;
	}
}

void	ast_expect_word(t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (!d->syntax_flag && (token == NULL || token->tk_type != WORD))
	{
		ast_syntax_error(d, token);
		// *current_token = token->next;
		return ;
	}
}

void	ast_expect_operator(t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (d->syntax_flag || token == NULL || ast_is_opereter(token->tk_type))
		return ;
	ast_syntax_error(d, token);
}
