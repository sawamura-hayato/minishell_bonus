/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:52:38 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/23 15:14:59 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdbool.h>
# include <stddef.h>
# include "init.h"

// try
void	*try_malloc(size_t size);
void	*try_calloc(size_t count, size_t size);
char	*try_strdup(const char *s1);
char	*try_substr(char const *s, size_t start, size_t len);
char	*try_strjoin(char const *s1, char const *s2);
void	try_write(int fildes, const void *buf, size_t nbyte, t_data *d);
char	*try_itoa(int n);
char	*try_strjoin_free(char *free_str, const char *str2);
int		try_open(int open_value, t_data *d);
void	try_close(int fildes, t_data *d);
void	try_dup(int fildes, t_data *d);
void	try_dup2(int fildes, int fildes2, t_data *d);

// ft
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
bool	ft_is_operator(char c);
int		ft_isspace(char c);
bool	ft_is_special_char(char c);
void	*ft_memchr(const void *s, int c, size_t n);
bool	ft_isupper(char c);
bool	ft_islower(char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp_ignorecase(const char *s1, const char *s2);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_isdigit(char c);

#endif