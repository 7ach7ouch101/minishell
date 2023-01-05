#include "../minishell.h"

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