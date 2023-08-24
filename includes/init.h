/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:15:31 by tterao            #+#    #+#             */
/*   Updated: 2023/08/17 14:21:26 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <unistd.h>
# include <stdbool.h>

enum
{
	UNDERLINE = 26,
	HASHMAP_SIZE = 27,
};

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
	bool syntax_flag;
	char	*pwd;
	char	*oldpwd;
}	t_data;

void	envs_init(const char **environ, t_data *d);
void	envs_newnode(char *_key, char *_value, t_envs **envs_hashmap);
void	envs_modify(char *_key, char *new_value, t_envs **envs_hashmap);
void	envs_addstr(char *_key, char *adding_value, t_envs **envs_hashmap);
void	envs_delete(char *_key, t_envs **envs_hashmap);
char	**envs_make_envp(t_envs **envs_hashmap);
void	envs_free_node(t_envs *node);
t_envs	*envs_get_node(const char *_key, t_envs **envs_hashmap);
char	*envs_get_value(const char *_key, t_envs **envs_hashmap);
size_t	envs_get_hashmap_index(char alpha);
// int		ft_strcmp(const char *s1, const char *s2);
// int		ft_isupper(char c);
// int		ft_islower(char c);

#endif
