/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:11:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/29 00:52:36 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"

int	main(void)
{
	t_data				d;
	extern const char	**environ;

	envs_init(environ, &d);
	read_eval_print_loop(&d);
	return (0);
}
