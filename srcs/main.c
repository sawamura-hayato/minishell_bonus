/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:11:21 by hsawamur          #+#    #+#             */
/*   Updated: 2023/09/15 18:41:29 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "init.h"

void	ignore_signal(t_data *d);

int	main(void)
{
	t_data				d;
	extern const char	**environ;

	d.exit_status = 0;
	ignore_signal(&d);
	envs_init(environ, &d);
	read_eval_print_loop(&d);
	return (0);
}
