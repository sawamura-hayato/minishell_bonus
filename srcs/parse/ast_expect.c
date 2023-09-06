/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:51:18 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/06 18:38:36 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ast_expect(t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if ((!d->syntax_flag) && (token == NULL || token->tk_type != TK_CLOSE_PARENTHESIS))
	{
		ast_syntax_error(d, token);
		return ;
	}
}
