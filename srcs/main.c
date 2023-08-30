/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:11:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/30 15:55:38 by tterao           ###   ########.fr       */
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
