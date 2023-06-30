/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:23 by hsawamur          #+#    #+#             */
/*   Updated: 2023/06/30 15:27:10 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

//expansion
void		expansion(t_ast *node, const t_envs **envs);
void		expand_variable(t_ast *node, const t_envs **envs);
void		expand_word_splitting(t_ast *node);//IFSを確認
void		expand_filename(t_ast *node);
void		expand_quotation(t_ast *node);
char		*get_env_x(char *target, const t_env **envs);
t_command	*command_add_node(t_command **head, t_command *where, t_command *newnode);
t_redirect	*redirect_add_node(t_redirect **head, t_redirect *where, t_redirect *newnode);

//heredoc
void		do_heredoc(t_ast *node);
void		expand_heredoc(t_ast *node, const t_envs **envs);

void	expansion(t_ast *node)
{
	if (node->left_hand != NULL)
		expansion(node->left_hand);
	if (node->right_hand != NULL)
		expansion(node->right_hand);
	expand_variable(node);
	expand_word_splitting(node);
	expand_filename(node);
	expand_quotation(node);
	do_heredoc(node);
	expand_heredoc(node);
}

#endif