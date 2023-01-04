#include "minishell.h"

/*void    allocate_name(char *s1, t_env *env)
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
    env1 = head;
    return (head);
}

t_env   *creat_env_node(char *name, char *value)
{
    t_env   *tmp;

    tmp = malloc(sizeof(t_env));
    if (!tmp)
        return (NULL);
    tmp->name = name;
    tmp->content = value;
    return (tmp);
}

int env_name_len(char *str)
{
    int len;

    len = 0;
    if (!str)
        return (len);
    while (str[len] && str[len] != '=')
        len++;
    return (len);
}

t_env   *fill_env(char **envp, t_env *env)
{
    int i;
    int name_len;
    char    *name;
    char    *value;
    t_env   *tmp;

    i = 0;
    if (!envp)
        return (NULL);
    env = creat_env_node(NULL, NULL);
    tmp = env;
    while (envp[i])
    {
        name_len = env_name_len(envp[i]);
        name = malloc(sizeof(char) * (name_len + 1));
        ft_strlcpy(name, envp[i], name_len + 1);
        value = malloc(sizeof(char) * (ft_strlen(&envp[i][name_len]) + 1));
        ft_strlcpy(value, &envp[i][name_len], (ft_strlen(&envp[i][name_len]) + 1));
        tmp->name = name;
        tmp->content = value;
        tmp->next = creat_env_node(NULL, NULL);
        tmp = tmp->next;
        i++;
    }
    return (env);
}*/



t_env	*ft_lstneww(char *v_name, char *v_value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = v_name;
	new->content = v_value;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_backk(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_env	*creat_list(char **str)
{
	t_env	*p;
	char	**splited;
	int		i;

	i = 0;
	p = NULL;
	while (str[i])
	{
		splited = ft_split(str[i], '=');
		ft_lstadd_backk(&p, ft_lstneww(splited[0], splited[1]));
		i++;
		free(splited);
	}
	return (p);
}