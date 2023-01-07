#include "../../minishell.h"
void    free_node(t_env *tmp)
{
    free(tmp->content);
    free(tmp->name);
    free(tmp);
}

void    ft_unset(t_env **env, t_cmd *cmd)
{
    t_env *head;
    t_env *tmp;
    int i;

    i = 1;
    /*if(ft_strcmpp((*env)->name, cmd->content[i]) == 0)
    {
        tmp = *env; 
        (*env) = (*env)->next;
        free_node(tmp);
        ft_lstclear(env, tmp);
        i++;
    }*/

    head = (*env);
    while(cmd->content[i])
    {
        while(head)
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