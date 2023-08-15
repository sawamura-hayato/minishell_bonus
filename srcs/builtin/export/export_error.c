/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:43:40 by tterao            #+#    #+#             */
/*   Updated: 2023/08/15 17:11:45 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include "init.h"
#include <stdlib.h>

void	export_invalid_identifier(char *str, t_data *d)
{
	char	*err_msg;

	d->exit_status = EXIT_FAILURE;
	err_msg = try_strdup("export: `");
	err_msg = try_strjoin_free(err_msg, str);
	err_msg = try_strjoin_free(err_msg, "\': not a valid identifier\n");
	try_write(STDERR_FILENO, err_msg, ft_strlen(err_msg), d);
	free(err_msg);
}
