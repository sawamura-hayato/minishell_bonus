/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_getcwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsawamur <hsawamur@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:15:18 by hsawamur          #+#    #+#             */
/*   Updated: 2023/08/11 15:28:44 by hsawamur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* CELEBC10 */
#define _POSIX_SOURCE
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>

main() {
  if (chdir("/tmp") != 0)
    perror("chdir() to /tmp failed");
  if (chdir("/chdir/error") != 0)
    perror("chdir() to /chdir/error failed");
}
