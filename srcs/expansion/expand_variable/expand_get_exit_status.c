/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_exit_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:30:51 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/31 12:03:10 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*try_itoa(int n);

char	*expand_get_exit_status(char **word, unsigned int exit_status)
{
	(*word)++;
	return (try_itoa(exit_status));
}
