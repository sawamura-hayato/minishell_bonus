/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:23 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/26 15:50:20 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

//expansion
void		expand_variable(t_ast **head);
void		expand_word_splitting(t_ast **head);//IFSを確認
void		expand_filename(t_ast **head);
void		expand_quotation(t_ast **head);
t_command	*command_add_node(t_command **head, t_command *where, t_command *newnode);
t_redirect	*redirect_add_node(t_redirect **head, t_redirect *where, t_redirect *newnode);

//heredoc
void		do_heredoc(t_ast **head);
void		expand_heredoc(t_ast **head);

#endif