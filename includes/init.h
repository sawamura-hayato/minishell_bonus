/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:15:31 by tterao            #+#    #+#             */
/*   Updated: 2023/07/27 20:35:27 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}	t_envs;

typedef struct s_data
{
	t_envs	*envs;
	int		exit_status;
}	t_data;



t_envs	*envs_init(const char **environ);
t_envs	*envs_newnode(char *_key, char *_value);
void	envs_addback(t_envs **head);

#endif
