/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:54:31 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 20:54:31 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    join_and_init(char *str, t_env **env)
{
    int i;

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
}

void    import_arg(char *str, t_env **env)
{
    int i;
    char *str1;
    char *str2;

    i = 0;
    join_and_init(str, env);
    while(str[i])
    {
        if(charcmp(str[i], '=') == 0)
        {
            if(charcmp(str[i - 1], '+') == 0)
                ft_lstadd_backk(env, ft_lstneww(ft_strlcpy(&str1, str, i - 1), 
                ft_strlcpy(&str2, &str[i + 1], ft_strlen(&str[i]))));
            else
                ft_lstadd_backk(env, ft_lstneww(ft_strlcpy(&str1, str, i), 
                ft_strlcpy(&str2, &str[i + 1], ft_strlen(&str[i]))));
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