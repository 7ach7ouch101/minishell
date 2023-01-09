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
    if(is_digit(str[i]) == 0 && str[i + 1])
    {
        printf("exit\n");
        printf("%s: numeric argument required\n", str[i]);
        exit(0);
    }
    if(!str[i])
    {
        printf("exit\n");
        exit(0);
    }
    if(str[2])
    {
        printf("exit\n");
        printf("exit: too many arguments\n");
        return ;
    }
    //num = ft_atoi(str[i]);

}