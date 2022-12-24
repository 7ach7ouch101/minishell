#include "../../minishell.h"

void    ft_pwd(void)
{
    char cwd[1000];
    if(getcwd(cwd, sizeof(cwd)) == NULL)
        printf("pwd: Error occurred.\n");
    else
        printf("%s\n", cwd);
}