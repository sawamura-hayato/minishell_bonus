/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_set_oldpwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:07:28 by tterao            #+#    #+#             */
/*   Updated: 2023/08/30 14:40:09 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "library.h"
#include <stdlib.h>

void	export_set_oldpwd(const char *key, t_data *d)
{
	char	*new_oldpwd;

	if (ft_strcmp(key, "OLDPWD") != 0)
		return ;
	new_oldpwd = envs_get_value((char *)key, d->envs_hashmap);
	free(d->oldpwd);
	d->oldpwd = new_oldpwd;
}
