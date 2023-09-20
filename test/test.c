#include <unistd.h>
#include <stdio.h>

int main()
{
    // execve("/usr/bin/valgrind", (char *[]){"/usr/bin/valgrind", "./minishell", NULL}, (char *[]){"", NULL});
    execve("../minishell", (char *[]){"../minishell",  NULL}, (char *[]){"a", NULL});
    // perror("");
}
