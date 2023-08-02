/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterao <tterao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:49:23 by hsawamur          #+#    #+#             */
/*   Updated: 2023/07/27 20:26:54 by tterao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

//expansion
int			expansion(t_ast *node, const t_envs **envs);
void		expand_variable(t_ast *node, const t_envs **envs);//環境変数を展開
void		expand_word_splitting(t_ast *node);//IFSを確認 クオテーションで囲まれていない && スペースがある場合、線形リストのトークンを分割
void		expand_filename(t_ast *node);//＊の展開 + 線形リストのトークンを追加
void		expand_quotation(t_ast *node);//クオテーションの削除
char		*get_env_x(char *target, const t_env **envs);
t_command	*command_split_node(t_command *node);//word splittingでノードを分割
t_redirect	*redirect_add_node(t_redirect *node);//word splittingでノードを分割

//heredoc
void		do_heredoc(t_ast *node);//heredocを実行し、文字列を取得
void		expand_heredoc(t_ast *node, const t_envs **envs);//delimiterにクオテーションがない場合、環境変数を展開


t_command	*command_split_node(t_command *node)
{

	t_command	*next = node->next;
	//一番最初はnode->wordだけ変更する
	if (is_ifs(node->word, try_get_env("IFS", envs)))
	{
		//[testa   b   c+test] -> [testa] [b   c+test]
		char	*tmp = node->word;
		node->word = try_substr(node->word, 0, strchr(node->word, try_get_env("IFS", envs)) - node->word[0]);
		t_command	*newnode = try_strdup(strchr(node->word, try_get_env("IFS", envs)));
		free(tmp);
	}
	//ifs区切り文字がある限りloop
	//[testa] [b   c  test] -> [b] [c+test]
	//final result = [a] [b] [c+test]
	while (is_ifs(node->word, try_get_env("IFS", envs)))
	{
		//ifs区切り文字がwordにあった場合、その文字アドレスを取得
		//command_newnodeの中で、strchrの返り値のアドレスをstrdupする
		t_command	*tmp = node;
		newnode = command_newnode(strchr(is_ifs(node->word, try_get_env("IFS", envs))));
		tmp->next = newnode;
	}
	newnode->next = next;
}

int	expansion(t_ast *node, t_envs **envs)
{
	int	ret;
	if (node->left_hand != NULL)
		ret = expansion(node->left_hand);
	if (ret)
		return;
	if (node->right_hand != NULL)
		ret = expansion(node->right_hand);
	if (ret)
		return;
	expand_variable(node);
	expand_word_splitting(node, envs);
	expand_filename(node);
	expand_quotation(node);
	if (do_heredoc(node))
	{
		//signalの対応
		return (1);
	}
	expand_heredoc(node);
	return (0);
}

#endif