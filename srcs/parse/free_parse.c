#include "parse.h"

static void word_list_free(t_word_list *head)
{
	t_word_list *word_p;
	t_word_list *tmp;

	word_p = head;
	while(word_p)
	{
		tmp = word_p->next;
		free(word_p->word);
		free(word_p->type);
		free(word_p);
		word_p = tmp;
	}
}

static void redirect_list_free(t_redirect_list *head)
{
		t_redirect_list *redirect_p;
		t_redirect_list *tmp;

		redirect_p = head;
		while(redirect_p)
		{
			tmp =redirect_p->next;
			free(redirect_p->word);
			free(redirect_p->redirect_type);
			free(redirect_p);
			redirect_p = tmp;
		}
}

void	ast_free_all_nodes(t_ast *node)
{
	if (node != NULL && node->left_hand != NULL)
		ast_free_all_nodes(node->left_hand);
	if (node != NULL && node->right_hand != NULL)
		ast_free_all_nodes(node->right_hand);
	if(node->type == PS_COMMAND)
	{
		word_list_free(node->command_list->word_list);
		redirect_list_free(node->command_list->redirect_list);
	}
	free(node);
}
