/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:11:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/08 15:39:16 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"

int	main(void)
{
	t_data				d;
	extern const char	**environ;

	d.exit_status = 0;
	envs_init(environ, &d);
	read_eval_print_loop(&d);
	return (0);
}
