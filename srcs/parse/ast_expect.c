/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 22:51:18 by tyamauch          #+#    #+#             */
/*   Updated: 2023/08/27 22:51:38 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ast_expect(t_token **current_token, char op, t_data *d)
{
	t_token	*token;

	token = *current_token;
	if (token->type != WORD || token->word[0] != op)
	{
		ast_syntax_error(d, token);
		return ;
	}
	token = token->next;
}
