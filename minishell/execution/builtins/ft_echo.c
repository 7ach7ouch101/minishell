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
    if(ft_strcmpp(str[i], "-n") == 0)
    {
        check = 0;
        i++;
    }
    else
        check = 1;
    while(str[i])
    {
        printf("%s",str[i]);
        i++;
    }
    if(check)
        printf("\n");
    return ;
}
