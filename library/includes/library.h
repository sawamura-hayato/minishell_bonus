/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:52:38 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/05 17:58:29 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdbool.h>
# include <stddef.h>

void	*try_malloc(size_t size);
void	*try_calloc(size_t count, size_t size);
char	*try_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
bool	ft_is_operator(char c);
int		ft_isspace(char c);
char	*try_substr(char const *s, size_t start, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
bool	ft_isupper(char c);
bool	ft_islower(char c);
int		ft_strcmp(const char *s1, const char *s2);

#endif