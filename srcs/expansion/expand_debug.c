#include "expansion.h"
#include "parse.h"

int printf(const char *format, ...);

void	debug_printf_test(char *testA, char *testB)
{
	static size_t i = 0;

	printf("[test: %zu]\n", i++);
	if (testA != NULL && testB != NULL)
	{
		if (ft_strcmp(testA, testB))
			printf("\e[0;32mok\033[0m\n");
		else
			printf("\e[0;31mko\033[0m\n");
	}
	printf("expect   %s\n", testA);
	printf("output   %s\n", testB);
}

void	debug_printf_word_list(t_word_list *word_list)
{
	while (word_list != NULL)
	{
		printf("word   %s\n", word_list->word);
		word_list = word_list->next;
	}
}

void	debug_free_word_list(t_word_list *word_list)
{
	// (void)word_list;
	t_word_list	*tmp_word;

	if (word_list == NULL)
		return ;
	tmp_word = word_list->next;
	while (tmp_word != NULL)
	{
		printf("word_list_free   %s\n", word_list->word);
		free(word_list);
		word_list = tmp_word;
		tmp_word = word_list->next;
	}
	printf("word_list_free   %s\n", word_list->word);
	free(word_list);
}

t_redirect	*debug_new_redirect_list(char *word, size_t index, t_redirect_type type)
{
	t_redirect	*new_redirect_list;

	new_redirect_list = try_malloc(sizeof(t_redirect));
	new_redirect_list->word = word;
	new_redirect_list->index = index;
	new_redirect_list->type = type;
	new_redirect_list->next = NULL;
	return (new_redirect_list);	
}

t_word_list	*debug_new_word_list(char *word, size_t index, t_token_type type)
{
	t_word_list	*new_word_list;

	new_word_list = try_malloc(sizeof(t_word_list));
	new_word_list->word = word;
	new_word_list->index = index;
	new_word_list->type = type;
	new_word_list->next = NULL;
	return (new_word_list);	
}

t_command	*debug_new_command(t_word_list *word_list, t_redirect *redirect_list)
{
	t_command	*new_command;

	new_command = try_malloc(sizeof(t_command));
	new_command->word_list = word_list;
	new_command->redirect_list = redirect_list;
	return (new_command);	
}

t_ast	*debug_new_ast(t_command *command, t_ast_node_type type)
{
	t_ast	*new_ast;

	new_ast = try_malloc(sizeof(t_ast));
	new_ast->command_list = command;
	new_ast->type = type;
	new_ast->left_hand = NULL;
	new_ast->right_hand = NULL;
	return (new_ast);	
}
