#include "../../minishell.h"

void    print_env(t_env *env)
{
    while(env)
    {   
        printf("declare -x %s=\"%s\"\n", env->name, env->content);
        env = env->next;
    }
}
int is_numor_char(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}
int charcmp(char c, char d)
{
    if(c == d)
        return (0);
    return (1);
}
int parse(char *str)
{
    int i;
    int check;

    i = 0;
    check = 0;
    if(!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
        return (0);
    i++;
    while(charcmp(str[i], '=') != 0 && str[i])
    {
        if(charcmp(str[i], '+') == 0 && charcmp(str[i + 1] , '=') == 0)
            i++;
        else if(is_numor_char(str[i]) == 0 && (str[i] != '_'))
            return (0);
        else
            i++;
    }
    return (1);
}

void    import_arg(char *str, t_env **env)
{
    /*int i;
    char *str1;
    i = 0;
    while(str[i])
    {
        if(charcmp(str[i], '=') == 0)
        {
            //printf("test\n");
            //ft_lstadd_backk(env, ft_lstneww(ft_strlcpy(str1, str, i), "test1"));
            break ;
        }
        i++;
    }*/
}

void    ft_export(char **str, t_env **env)
{ 
    //ft_lstadd_backk(env, ft_lstneww("test", "test1"));
    int i;

    i = 1;
    if(!(str[1]))
        print_env(*env);
    else
    {
        while(str[i])
        {
            if (parse(str[i]) == 0)
                printf("export: %s: not a valid identifier\n", str[i]);
            else
            {
                ft_lstadd_backk(env, ft_lstneww("test", "test1"));
                //import_arg(str[i] , env);  
            }
            //printf("test\n");
            i++;
        }
    }
}