#include "../../minishell.h"
void    free_node(t_env *tmp)
{
    free(tmp->content);
    free(tmp->name);
    free(tmp);
}
void    first_node(t_env **env, char *str)
{
    t_env *tmp;

    if(ft_strcmpp((*env)->name, str) == 0)
    {
        tmp = *env; 
        (*env) = (*env)->next;
        free_node(tmp);
    }
}
void    ft_unset(t_env **env, t_cmd *cmd)
{
    t_env *head;
    t_env *tmp;
    int i;

    g_exit_status = 0;
    i = 1;
    head = (*env);
    while(cmd->content[i] && cmd->content[i][0])
    {
        first_node(env , cmd->content[i]);
        while(head && head->next)
        {
            if(ft_strcmpp(head->next->name, cmd->content[i]) == 0)
            {
                tmp = head->next;
                head->next = head->next->next;
                free_node(tmp);
                break ;
            }
            head = head->next;
        }
        head = *env;
        i++;
    }
}