#include "parse.h"

void debug_print_ast(t_ast *node)
{
    t_redirect_list *redirect_p;
    t_word_list *word_p;

    if ( node->left_hand != NULL)
        debug_print_ast(node->left_hand);
    if (node->right_hand != NULL)
        debug_print_ast(node->right_hand);
    printf("===========debug==================\n");
    printf("ast_node_type:[%d]\n", node->type);
    if(node->command_list == NULL)
        return;
    word_p = node->command_list->word_list;
    redirect_p = node->command_list->redirect_list;
    while(word_p != NULL)
    {
        printf("word_list:[%s] ", word_p->word);
        printf("type:[%d]\n", word_p->type);
        word_p = word_p->next;
    }
    while(redirect_p !=NULL)
    {
        printf("redirect_list:[%s] ",redirect_p->word);
        printf("type:[%d]\n",redirect_p->type);
        redirect_p = redirect_p->next;
    }
    printf("===========debug==================\n");
}
