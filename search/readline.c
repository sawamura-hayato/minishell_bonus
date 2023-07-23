#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tokenize.h"
#include <string.h>
#include <stdlib.h>
int main(void)
{
	char	*line;
	t_token *token;


	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || strlen(line) == 0)
			break;
		token = create_token(create_word(line, DEFAULT), WORD, 0);
		debug_print_token(token);
		free(line);
	}
	printf("exit\n");
	return (0);
}