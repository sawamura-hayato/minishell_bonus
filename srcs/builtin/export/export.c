/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tatyu <tatyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:54:16 by tterao            #+#    #+#             */
/*   Updated: 2023/08/11 15:13:24 by tatyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "init.h"

void	export_show(t_data *d);

void	builtin_export(char **argv, t_data *d)
{
	if (argv[1] == NULL)
		export_show(d);
}
