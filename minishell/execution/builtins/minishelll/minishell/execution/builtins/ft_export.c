#include "../../minishell.h"

void    print_env(t_env *env)
{
    while(env)
    {   
        printf("declare -x %s=\"%s\"\n", env->name, env->content);
        env = env->next;
    }
}

int is_alnumr(char c)
{
    return (c == '_' || (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int parse(char *str)
{
    int i;

    i = 0;
    while (str[i] && is_alnumr(str[i]))
        i++;
    if (str[i] && (str[i] == '=' || str[i] == '+'))
    {
        if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
            return (1);
    }
    else if (str[i] == '\0')
        return (1);
    return (0);
    // if(!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
    //     return (0);
    // return (1);
}

void    import_arg(char *str, t_env **env)
{
    ft_lstadd_backk(env, ft_lstneww("test", "test1"));
}

void    ft_export(char **str, t_env **env)
{ 
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
                import_arg(*str , env);  
            //ft_lstadd_backk(env, ft_lstneww("test", "test1"));
            i++;
        }
    }
}