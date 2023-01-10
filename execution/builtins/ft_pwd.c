#include "../../minishell.h"

void    ft_pwd(void)
{
    char cwd[1000];

    g_exit_status = 0;
    if(getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("pwd: Error occurred.\n");
        g_exit_status = 1;
    }
    else
        printf("%s\n", cwd);
}