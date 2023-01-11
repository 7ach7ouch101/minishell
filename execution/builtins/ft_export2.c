/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:55:58 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 21:54:47 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (!(env->content) && ((ft_strcmp(env->name, "PATH"))
				|| (!ft_strcmp(env->name, "PATH")
					&& ft_strncmp(env->content, "d:", 2))))
			printf("declare -x %s\n", env->name);
		else if (((ft_strcmp(env->name, "PATH"))
				|| (!ft_strcmp(env->name, "PATH")
					&& ft_strncmp(env->content, "d:", 2))))
			printf("declare -x %s=\"%s\"\n", env->name, env->content);
		env = env->next;
	}
}

int	check_ifitsthere(char *str, t_env *env)
{
	char	*str1;
	int		i;

	i = 0;
	while (env)
	{
		i = 0;
		while ((charcmp(str[i + 1], '=') == 1 && charcmp(str[i], '+') == 1)
			&& str[i])
			i++;
		if (charcmp(str[i], '=') == 0)
			i++;
		if (charcmp(str[i], '+') == 0)
			i--;
		if (ft_strcmpp(ft_strlcpy(&str1, str, i + 1), env->name) == 0)
		{
			free(str1);
			return (0);
		}
		free(str1);
		env = env->next;
	}
	return (1);
}

int	parse(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')))
		return (0);
	i++;
	while (charcmp(str[i], '=') != 0 && str[i])
	{
		if (charcmp(str[i], '+') == 0 && charcmp(str[i + 1], '=') == 0)
			i++;
		else if (is_numor_char(str[i]) == 0 && (str[i] != '_'))
			return (0);
		else
			i++;
	}
	return (1);
}

void	init_content(char *str, t_env *env)
{
	int		i;
	char	*str1;

	while (env)
	{
		i = 0;
		while (charcmp(str[i], '=') != 0)
			i++;
		if (ft_strcmpp(ft_strlcpy(&str1, str, i), env->name) == 0)
		{
			free(env->content);
			env->content = ft_strdup(&str[i + 1]);
			free(str1);
			return ;
		}
		free(str1);
		env = env->next;
	}
}

void	join_content(char *str, t_env *env)
{
	int		i;
	char	*str1;
	char	*to_free;

	while (env)
	{
		i = 0;
		while (charcmp(str[i], '+') != 0)
				i++;
		if (ft_strcmpp(ft_strlcpy(&str1, str, i), env->name) == 0)
		{
			free(str1);
			if (!env->content)
				env->content = ft_strjoin(&str[i + 2], "");
			else
			{
				to_free = env->content;
				env->content = ft_strjoin(env->content, &str[i + 2]);
				free(to_free);
			}
			return ;
		}
		free(str1);
		env = env->next;
	}
}
