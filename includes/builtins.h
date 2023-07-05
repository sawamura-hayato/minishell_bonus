/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:42:06 by tterao            #+#    #+#             */
/*   Updated: 2023/07/05 13:03:42 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		do_builtin(t_ast *node);
void	builtin_echo(t_ast *node);
void	builtin_cd(t_ast *node);
void	builtin_pwd(t_ast *node);
void	builtin_export(t_ast *node);
void	builtin_unset(t_ast *node);
void	builtin_env(t_ast *node);
void	builtin_exit(t_ast *node);

#endif