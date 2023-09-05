/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:51:18 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/05 19:07:08 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ast_expect(t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (token == NULL || token->tk_type != TK_CLOSE_PARENTHESIS)
	{
		ast_syntax_error(d, token);
		return ;
	}
}
