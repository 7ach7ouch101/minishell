#include "../../minishell.h"

int ft_strcmpp(char *str1, char *str2)
{
    int i ;

    i = 0;
    if(!str1 || !str2)
        return (1);
    while(str1[i] && str2[i] && str1[i] == str2[i])
        i++;
    return (str1[i] - str2[i]);
}

void  ft_echo(char **str)
{
    int i;
    int check;

    i = 1;
    check = 0;
    while (ft_ncmp(str[i]) == 0)
    {
        check ++;
        i++;
    }
    while(str[i])
    {
        printf("%s",str[i]);
        i++;
    }
    if(!check)
        printf("\n");
    g_exit_status = 0;
    return ;
}
