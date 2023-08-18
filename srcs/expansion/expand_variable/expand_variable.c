/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:21:54 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/15 14:40:52 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
// #include <stdio.h>

int printf(const char *format, ...);
void debug_printf_test(char *testA, char *testB);

void expand_variable(t_ast *node, t_data *d)
{
	if (node->command_list != NULL)
	{
		expand_variable_word_list(&(node->command_list->word_list), d);
		expand_variable_redirect_list(&(node->command_list->redirect_list), d);
	}
	else
		printf("operator\n");
}
