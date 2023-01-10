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

void	update_shlvl(t_env *env, char ***str, int i)
{
	int	old;

	old = ft_atoi(ft_envlast(env)->content);
	free(ft_envlast(env)->content);
	ft_envlast(env)->content = ft_itoa(old + 1);
	(*str)[i] = ft_strjoin("SHLVL=", ft_envlast(env)->content);
}

void	ft_empty_env(t_env **env, char ***str)
{
	char pwd_str[1000];

	getcwd(pwd_str, sizeof(pwd_str));
	ft_lstadd_backk(env, ft_lstneww(ft_strdup("_"), ft_strdup("/usr/bin/env")));
	ft_lstadd_backk(env, ft_lstneww(ft_strdup("PATH"), ft_strdup(PATH)));
	ft_lstadd_backk(env, ft_lstneww(ft_strdup("PWD"), ft_strdup(pwd_str)));
	ft_lstadd_backk(env, ft_lstneww(ft_strdup("SHLVL"), ft_itoa(1)));
	(*str) = malloc(sizeof(char *) * 5);
	(*str)[0] = ft_strjoin("SHLVL=", ft_envlast(*env)->content);
	(*str)[1] = ft_strdup("_=/usr/bin/env");
	(*str)[2] = ft_strjoin("PATH=", PATH);
	(*str)[3] = ft_strjoin("PWD=", pwd_str);
	(*str)[4] = NULL;
}

t_env	*create_list(char ***str)
{
	t_env	*env;
	char	**str1;
	int		i;
	int		j;

	i = 0;
	env = NULL;
	if(!(*str)[i])
		ft_empty_env(&env, str);
	else
	{
		while ((*str)[i])
		{
			str1 = ft_split((*str)[i], '=');
			ft_lstadd_backk(&env, ft_lstneww(str1[0], str1[1]));
			if (ft_strncmp((*str)[i], "SHLVL", 5) == 0)
				update_shlvl(env, str, i);
			i++;
			free(str1);
		}
	}
	return (env);
}