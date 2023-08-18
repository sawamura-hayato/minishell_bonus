#include "parse.h"
#include <stdio.h>

void	ast_syntax_error(t_data *d)
{
	printf("syntax_error");
	d->exit_status = 2;
	d->syntax_flag = true;
}
