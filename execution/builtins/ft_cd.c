/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:26:06 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 13:26:06 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*update_env(t_env *env, char *old_wd)
{
	t_env	*head;
	char	pwd[1000];

	head = env;
	while (env)
	{
		if (ft_strcmpp(env->name, "PWD") == 0)
		{
			if (getcwd(pwd, sizeof(pwd)) == NULL)
			{
				printf("\n");
				g_exit_status = 1;
			}
			free(env->content);
			env->content = ft_strdup(pwd);
		}
		if (ft_strcmpp(env->name, "OLDPWD") == 0)
		{
			free(env->content);
			env->content = ft_strdup(old_wd);
		}
		env = env->next;
	}
	return (env);
}

int	get_the_path(t_env *env, char *str)
{
	while (env)
	{
		if (ft_strcmpp(env->name, str) == 0)
		{
			if (chdir(env->content) == -1)
			{
				printf("cd: Error occurred.\n");
				g_exit_status = 1;
				return (0);
			}
			return (0);
		}
		env = env->next;
	}
	if (ft_strcmpp(str, "HOME") == 0)
	{
		printf("cd : HOME not set\n");
		g_exit_status = 1;
		return (0);
	}
	if (ft_strcmpp(str, "OLDPWD") == 0)
		return (printf("cd : OLDPWD not set\n"), g_exit_status = 1, 0);
	return (0);
}

void	ft_cd(char **str, t_env *env)
{
	char	old_wd[1000];

	g_exit_status = 0;
	if (getcwd(old_wd, sizeof(old_wd)) == NULL)
	{
		printf("cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory.\n");
		g_exit_status = 1;
		return ;
	}
	if (ft_strcmpp(str[1], "-") == 0)
		get_the_path(env, "OLDPWD");
	else if (ft_strcmpp(str[1], "~") == 0 || !str[1])
		get_the_path(env, "HOME");
	else
	{
		if (chdir(str[1]) == -1)
		{
			printf("cd: path not found.\n");
			g_exit_status = 1;
		}
	}
	env = update_env(env, old_wd);
}
