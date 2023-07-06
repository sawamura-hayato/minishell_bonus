/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:23 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/06 17:36:29 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

//expansion
void		expansion(t_ast *node, const t_envs **envs);
void		expand_variable(t_ast *node, const t_envs **envs);//環境変数を展開
void		expand_word_splitting(t_ast *node);//IFSを確認 クオテーションで囲まれていない && スペースがある場合、線形リストのトークンを分割
void		expand_filename(t_ast *node);//＊の展開 + 線形リストのトークンを追加
void		expand_quotation(t_ast *node);//クオテーションの削除
char		*get_env_x(char *target, const t_env **envs);
t_command	*command_add_node(t_command **head, t_command *where, t_command *newnode);
t_redirect	*redirect_add_node(t_redirect **head, t_redirect *where, t_redirect *newnode);

//heredoc
void		do_heredoc(t_ast *node);//heredocを実行し、文字列を取得
void		expand_heredoc(t_ast *node, const t_envs **envs);//delimiterにクオテーションがない場合、環境変数を展開

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