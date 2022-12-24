#include "../../minishell.h"

void    get_the_path(t_env *env, char *str)
{
    while(env->next)
    {
        if(ft_strcmpp(env->name, str) == 0)
        {
            if(chdir(env->content) == -1)
            {
                printf("cd: Error occurred.\n");
                return ;
            }
        }
        env = env->next;
    }
}
void    ft_cd(char **str, t_env *env)
{
    if(ft_strcmpp(str[1],"-") == 0)
        get_the_path(env, "OLDPWD");
    else if(ft_strcmpp(str[1],"~") == 0 || !str[1])
        get_the_path(env, "HOME");
    else
    {
        if(chdir(str[1]) == -1)
            printf("cd: path not found.\n");
    }
}