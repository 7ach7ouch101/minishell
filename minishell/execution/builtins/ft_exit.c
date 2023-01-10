#include "../../minishell.h"
int is_digit(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}

void    ft_exit(char **str)
{
    int i;
    int num;

    i = 1;
    if(!str[i])
    {
        printf("exit\n");
        g_exit_status = 0;
        exit(0);
    }
    else if(is_digit(str[i]) == 0)
    {
        printf("exit\n");
        printf("%s: numeric argument required\n", str[i]);
        g_exit_status = 255;
        exit(255);
    }
    else if(str[2])
    {
        printf("exit\n");
        printf("exit: too many arguments\n");
        g_exit_status = 1;
        return ;
    }
    g_exit_status = ft_atoi(str[i]);
    exit(ft_atoi(str[i]));
}