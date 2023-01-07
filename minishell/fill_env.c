#include "minishell.h"

t_env	*ft_lstneww(char *env_name, char *env_content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = env_name;
	new->content = env_content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_backk(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*create_list(char **str)
{
	t_env	*env;
	char	**str1;
	int		i;

	i = 0;
	env = NULL;
	if(!str[i])
	{
		ft_lstadd_backk(&env, ft_lstneww(ft_strdup("SHLVL"), ft_strdup("1")));
	}
	while (str[i])
	{
		str1 = ft_split(str[i], '=');
		ft_lstadd_backk(&env, ft_lstneww(str1[0], str1[1]));
		i++;
		free(str1);
	}
	return (env);
}