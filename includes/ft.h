/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:52:32 by tterao            #+#    #+#             */
/*   Updated: 2023/07/08 13:57:14 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

void	*malloc_x(size_t size);
void	*strdup_x(const char *str);
void	*substr_x(const char *str, size_t start, size_t length);
int		close_x(int fd);

#endif