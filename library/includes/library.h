/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:52:38 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/06 13:08:43 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdbool.h>
# include <stddef.h>

// try
void	*try_malloc(size_t size);
void	*try_calloc(size_t count, size_t size);
char	*try_strdup(const char *s1);
char	*try_substr(char const *s, size_t start, size_t len);

// ft
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

#endif