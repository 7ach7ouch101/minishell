/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:05:23 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 23:25:32 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check(t_cmd *cmd)
{
	if (cmd->red)
	{
		if (red_test(cmd->red) == 0)
		{
			g_exit_status = 1;
			return (0);
		}
	}
	g_exit_status = 0;
	return (1);
}

void	exe_builtins(t_cmd *cmd, t_env **env)
{
	int	fd[2];

	fd[1] = dup(1);
	fd[0] = dup(0);
	if (check(cmd) == 0)
		return ;
	if (ft_strcmpp(cmd->content[0], "echo") == 0)
		ft_echo(cmd->content);
	else if (ft_strcmpp(cmd->content[0], "env") == 0)
		ft_env(cmd->content, *env);
	else if (ft_strcmpp(cmd->content[0], "cd") == 0)
		ft_cd(cmd->content, *env);
	else if (ft_strcmpp(cmd->content[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmpp(cmd->content[0], "unset") == 0)
		ft_unset(env, cmd);
	else if (ft_strcmpp(cmd->content[0], "export") == 0)
		ft_export(cmd->content, env);
	else if (ft_strcmpp(cmd->content[0], "exit") == 0)
		ft_exit(cmd->content);
	if (cmd->red)
	{
		dup2(fd[1], 1);
		dup2(fd[0], 0);
	}
}

int	check_builtins(char *str)
{
	if (ft_strcmpp(str, "echo") == 0)
		return (0);
	else if (ft_strcmpp(str, "env") == 0)
		return (0);
	else if (ft_strcmpp(str, "cd") == 0)
		return (0);
	else if (ft_strcmpp(str, "pwd") == 0)
		return (0);
	else if (ft_strcmpp(str, "unset") == 0)
		return (0);
	else if (ft_strcmpp(str, "export") == 0)
		return (0);
	else if (ft_strcmpp(str, "exit") == 0)
		return (0);
	return (1);
}

char	*find_path(t_env *env, t_cmd *cmd)
{
	char	**str;
	char	*tmp;
	int		i;

	i = 0;
	while (env->next)
	{
		if (ft_strcmpp(env->name, "PATH") == 0)
		{
			str = ft_split(env->content, ':');
			while (str[++i])
			{
				tmp = ft_strjoin(str[i], "/");
				if (access(ft_strjoin(tmp, cmd->content[0]), X_OK) == 0)
				{
					tmp = ft_strjoin(tmp, cmd->content[0]);
					break ;
				}
				free(tmp);
			}
		}
		env = env->next;
	}
	return (tmp);
}
