#include "minishell.h"
void    allocate_name(char *s1, t_env *env)
{
    int j;
    int i;
    int a;
    int b;

    a = 0;
    b = 0;
    i = 0;
    j = 0;
    while(s1[i] != '=')
        i++;
    env->name = malloc(i * sizeof(char));
    while(s1[j] != '=')
    {
        env->name[j] = s1[j];
        j++;
    }
    i++;
    while(s1[i + a])
        a++;
    env->content = malloc(a * sizeof(char));
    while(s1[i + b])
    {
        env->content[b] = s1[i + b];
        b++;
    }
}
t_env	*fillnodes(t_env **head)
{
	t_env	*sec;

	sec = malloc(sizeof(t_env));
	sec->next = (*head);
	return (sec);
}
void    allocate_nodes(t_env **env, int a)
{
    while(a >= 0)
    {
        (*env) = fillnodes(&(*env));
        a--;
    }
}
t_env   *fill_env(char **envp, t_env *env)
{
    t_env *head;
    int a;
    int i;

    env = NULL;
    a = 0;
    i = 0;
    while(envp[a])
        a++;
    allocate_nodes(&env, a);
    head = env;
    while(envp[i])
    {
        allocate_name(envp[i], env);
        env = env->next;
        i++;
    }
    return (head);
}