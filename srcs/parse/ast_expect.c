/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:51:18 by tyamauch          #+#    #+#             */
/*   Updated: 2023/09/07 18:01:23 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ast_expect(t_token_type expecting_type,
					t_token **current_token, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (!d->syntax_flag
		&& (token == NULL || token->tk_type != expecting_type))
	{
		ast_syntax_error(d, token);
		return ;
	}
}
