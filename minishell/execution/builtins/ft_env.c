#include "../../minishell.h"

void    ft_env(char **str, t_env *env)
{
    if(!str[1])
    {
        while(env)
        {
            printf("%s=%s\n", env->name, env->content);
            env = env->next;
        }
    }
    else
        printf("env: no arguments needed here\n");
}