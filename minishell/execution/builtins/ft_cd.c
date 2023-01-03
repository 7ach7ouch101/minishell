#include "../../minishell.h"

t_env    *update_env(t_env *env, char *old_wd)
{
    t_env *head;
    char pwd[1000];

    head = env;
    while(env)
    {
        if(ft_strcmpp(env->name, "PWD") == 0)
        {
            if(getcwd(pwd, sizeof(pwd)) == NULL)
                printf("Error occurred.\n");
            free(env->content);
            env->content = ft_strdup(pwd);
        }
        if(ft_strcmpp(env->name, "OLDPWD") == 0)
        {
            free(env->content);
            env->content = ft_strdup(old_wd);
        }
        env = env->next;
    }
    return env;
}

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
    char old_wd[1000];

    if(getcwd(old_wd, sizeof(old_wd)) == NULL)
        printf("Error occurred.\n");
    if(ft_strcmpp(str[1],"-") == 0)
        get_the_path(env, "OLDPWD");
    else if(ft_strcmpp(str[1],"~") == 0 || !str[1])
        get_the_path(env, "HOME");
    else
    {
        if(chdir(str[1]) == -1)
            printf("cd: path not found.\n");
    }
    env = update_env(env, old_wd);
}