/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:43:20 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/28 16:01:54 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "init.h"
# define NULL_CHAR ('\0')
# define PROMPT ("minishell$ ")

void	read_eval_print_loop(t_data *d);

#endif
