/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:15:31 by tterao            #+#    #+#             */
/*   Updated: 2023/08/03 19:07:43 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <unistd.h>
# include <stdbool.h>

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}	t_envs;

typedef struct s_data
{
	t_envs	**envs_hashmap;
	int		exit_status;
}	t_data;

void	envs_init(const char **environ, t_data d);
t_envs	*envs_newnode(char *_key, char *_value, t_envs **envs_hashmap);
void	*envs_modify(char *_key, char *new_value, t_envs **envs_hashmap);
void	*envs_addstr(char *_key, char *adding_value, t_envs **envs_hashmap);
void	*envs_delete(char *_key, t_envs **envs_hashmap);
bool	is_top(char alpha, char *_key);
t_envs	*get_node(char *_key);
int		get_hashmap_index(char alpha);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isupper(char c);
int		ft_islower(char c);

#endif
