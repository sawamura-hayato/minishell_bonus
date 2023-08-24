
#include "exec_command.h"
#include "expansion.h"

void	debug_printf_double_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("arr[%zu]   %s\n",i ,arr[i]);
		i++;
	}

}