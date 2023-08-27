#include "parse.h"
#include <stdio.h>

void	ast_syntax_error(t_data *d,t_token *token)
{
	if(token == NULL)
		printf("syntax error near unexpected token `newline'\n");
	else 
		printf("syntax error near unexpected token `%s'\n",token->word);
	d->exit_status = SYNTAX_ERROR;
	d->syntax_flag = true;
}

/* <ALPHA> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z| */
/*              A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z */

/* <DIGIT> ::= 0|1|2|3|4|5|6|7|8|9 */

/* <NUMBER> ::= <DIGIT> */
/*            | <NUMBER> <DIGIT> */

/* t_token_type WORD */
/* <WORD> ::= <ALPHA> */
/* 		 | <WORD> <ALPHA> */
/* 		 | <WORD> '_' */
/* 		 | <WORD> <NUMBER> */

/* t_token_type TK_PIPE */
/* t_token_type TK_LOGICAL_OR */
/* t_token_type TK_LOGICAL_AND */
/* t_token_type TK_OPEN_PARENTHESIS */
/* t_token_type TK_CLOSE_PARENTHESIS */
/* <OPERATOR> ::= '|' */
/* 			|  '||' */
/* 			|  '&&' */
/* 			|  '(' */
/* 			|  ')' */

/* <REDIRECTION> ::= '>' <WORD> */
/* 				| '<' <WORD> */
/* 				| '<<' <WORD> */
/* 				| '>>' <WORD> */
/* 				| '<>' <WORD> */

/* bash: syntax error near unexpected token `newline'> */
/* ./minishell > */
/* ./minishell < */
/* ./minishell << */
/* ./minishell >> */

/* hoge is not <WORD> <OPERATOR>*/
/* bash: syntax error near unexpected token `hoge */
/* ./minishell > hoge*/
/* ./minishell < hoge*/
/* ./minishell << hoge*/
/* ./minishell >> hoge*/

/* <WORD_LIST> ::= <WORD> */
/* 			|   <WORD_LIST> <WORD> */

/* <REDIRECTION_LIST> ::= <REDIRECTION> */
/* 					|  <REDIRECTION_LIST> <REDIRECTION> */

/* <COMMAND> ::= <WORD_LIST> */
/* 			| <REDIRECTION_LIST> */
/* 			| <OPERATOR> */

/* <COMMAND_LIST> ::= <COMMAND> */
/* 				|  <COMMAND_LIST> <COMMAND> */

