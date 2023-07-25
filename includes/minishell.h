/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:43:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/25 14:08:40 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define NULL_CHAR ('\0')
// #define SINGLE_QUOTE (')
// #define DOUBLE_QUOTE (")
#define PROMPT ("minishell$ ")

#include <stdio.h>
// t_token	*tokenize(const char *line);
void	read_eval_print_loop();
#endif