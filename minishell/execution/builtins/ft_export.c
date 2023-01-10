#include "../../minishell.h"

void    print_env(t_env *env)
{
    while(env)
    {
        if(!(env->content))
            printf("declare -x %s\n", env->name);
        else
            printf("declare -x %s=\"%s\"\n", env->name, env->content);
        env = env->next;
    }
}

int charcmp(char c, char d)
{
    if(c == d)
        return (0);
    return (1);
}

int check_ifitsthere(char *str, t_env *env)
{
    char *str1;
    int i;

    i = 0;
    while(env)
    {
        i = 0;
        while((charcmp(str[i + 1], '=') == 1 && charcmp(str[i], '+') == 1) && str[i])
            i++;
        if(charcmp(str[i], '=') == 0)
            i++;
        if(charcmp(str[i], '+') == 0)
            i--;
        if(ft_strcmpp(ft_strlcpy(str1 , str, i + 1), env->name) == 0)
            return (0);
        env = env->next;
    }
    return (1);
}

int is_numor_char(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
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

void    join_content(char *str, t_env *env)
{
    int i;
    char *str1;

    while(env)
    {
        i = 0;
        while(charcmp(str[i], '+') != 0)
                i++;
        if(ft_strcmpp(ft_strlcpy(str1 , str, i), env->name) == 0)
        {
            if(!env->content)
                env->content = ft_strjoin(&str[i + 2], "");
            else
                env->content = ft_strjoin(env->content, &str[i + 2]);
            return ;
        }
        env = env->next;
    }
}

void    init_content(char *str, t_env *env)
{
    int i;
    char *str1;

    while(env)
    {
        i = 0;
        while(charcmp(str[i], '=') != 0)
            i++;
        if(ft_strcmpp(ft_strlcpy(str1, str, i), env->name) == 0)
        {
            free(env->content);
            env->content = ft_strdup(&str[i + 1]);
            return ;
        }
        env = env->next;
    }
}

void    import_arg(char *str, t_env **env)
{
    int i;
    char *str1;
    char *str2;

    i = 0;
    if(check_ifitsthere(str, *env) == 0)
    {
        while(str[i])
        {
            if(charcmp(str[i], '+') == 0)
            {
                join_content(str, *env);
                return ;
            }
            else if(charcmp(str[i], '=') == 0)
                init_content(str, *env);
            i++;
        }
        return ;
    }
    while(str[i])
    {
        if(charcmp(str[i], '=') == 0)
        {
            if(charcmp(str[i - 1], '+') == 0)
                ft_lstadd_backk(env, ft_lstneww(ft_strlcpy(str1, str, i - 1), ft_strlcpy(str2, &str[i + 1], ft_strlen(&str[i]))));
            else
                ft_lstadd_backk(env, ft_lstneww(ft_strlcpy(str1, str, i), ft_strlcpy(str2, &str[i + 1], ft_strlen(&str[i]))));
            return ;
        }
        i++;
    }
    if(!str[i] && check_ifitsthere(str, *env) == 1)
        ft_lstadd_backk(env, ft_lstneww(ft_strdup(str), NULL));
}

void    ft_export(char **str, t_env **env)
{
    int i;

    i = 1;
    g_exit_status = 0;
    if(!(str[1]))
        print_env(*env);
    else
    {
        while(str[i])
        {
            if (parse(str[i]) == 0)
            {
                printf("export: %s: not a valid identifier\n", str[i]);
                g_exit_status = 1;
            }
            else
                import_arg(str[i] , env);
            i++;
        }
    }
}