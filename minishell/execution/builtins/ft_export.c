#include "../../minishell.h"

void    print_env(t_env *env)
{
    while(env->next)
    {
        printf("declare -x %s=\"%s\"\n", env->name, env->content);
        env = env->next;
    }
}
int parse(char *str)
{
    int i;

    i = 0;
    if(!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
        return (0);
    return (1);
}
t_env    *import_arg(char *str, t_env *env)
{
    t_env *t;
    t_env *head;

    head = env;
    while(env->next)
        env = env->next;
    t = malloc(sizeof(t_env));
    env->next = t;
    t->name = ft_strdup("test");
    t->content = ft_strdup("haa");
    t->next = NULL;
    return (head);
}
void    ft_export(char **str, t_env *env)
{ 
    int i;

    i = 1;
    if(!(str[1]))
        print_env(env);
    while(str[i])
    {
        if(parse(str[i]) == 0)
        {
            printf("export: %s: not a valid identifier\n", str[i]);
            return ;
        }
        env = import_arg(str[i], env);
        /*while(env->next)
        {
            printf("%s\n", env->name);
            env = env->next;
        }*/
        i++;
    }
}