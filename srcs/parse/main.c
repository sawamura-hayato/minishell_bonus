#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../includes/parse.h"

int main()
{
	t_token *token_command;
	t_token *token_pipe;
	t_token *token_p;
	t_data *d;
	char word1[] = "42tokyo";
	char word2[] = "|";
	
	/* token_command = create_token("42 Tokyo",WORD,0); */ 
	token_command = calloc(1,sizeof(t_token));
	token_pipe = calloc(1,sizeof(t_token));
	/* token_pipe = create_token("|",PIPE,1); */
	token_p = token_command;
	token_command -> word = strdup(word1);
	token_command -> type = WORD;
	token_command -> index = 0;
	token_command -> next = token_pipe;

	token_pipe -> word = strdup(word2);
	token_pipe -> type = PIPE;
	token_pipe -> index = 1;
	token_pipe -> next = NULL;

	while(token_p)
	{
		printf("%s\n",token_p -> word);
		token_p = token_p-> next;
	}
	/* parse(token,d); */
	ast_command_node(&token_command,d);
}
