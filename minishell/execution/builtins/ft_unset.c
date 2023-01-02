#include "../../minishell.h"
void    free_node(t_env *tmp)
{
    free(tmp->content);
    free(tmp->name);
    free(tmp);
}

t_env    *ft_unset(t_env **envhead, t_cmd *cmd)
{
    t_env *head;
    t_env *tmp;
    t_env *env = *envhead;
    t_env *bak = *envhead;
    int i;

    i = 1;
    if(ft_strcmpp(env->name, cmd->content[i]) == 0)
    {
        tmp = env; 
        bak = env->next;
        free_node(tmp);
        i++;

    }
    head = env;
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
        head = env;
        i++;
    }
    *envhead = bak;
    return NULL;
}