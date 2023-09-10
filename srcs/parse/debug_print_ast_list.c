/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_ast_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:00:34 by tterao            #+#    #+#             */
/*   Updated: 2023/09/10 16:46:11 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	debug_print_ast_list(t_ast_list *root)
{
	t_ast_list	*p;

	p = root;
	while (p != NULL)
	{
		debug_print_ast(p->ast);
		printf("\n\n");
		p = p->next;
	}
}
