/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:41:47 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 20:41:47 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_cmd(t_cmd *cmd, t_env *env, char **envp)
{
	char	*tmp;

	if (!cmd->content[0] || !cmd->content)
		exit(0);
	if (ft_strncmp(cmd->content[0], ".", 1)
		&& ft_strncmp(cmd->content[0], "/", 1))
		tmp = find_path(env, cmd);
	if (execve(tmp, cmd->content, envp) < 0)
		return (printf("%s: command not found\n", cmd->content[0]), exit(127));
}

void	absolute_path(t_cmd *cmd, char **envp)
{
	if (!cmd->content[0] || !cmd->content)
		exit(0);
	if (access(cmd->content[0], X_OK) == 0)
	{
		if (execve(cmd->content[0], cmd->content, envp) < 0)
		{
			printf("%s: command not found\n", cmd->content[0]);
			exit(127);
		}
	}
}

void	exe_cmd(t_cmd *cmd, t_env **env, char **envp, int fd[])
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->next)
		ft_pipe(fd);
	if (red_test(cmd->red) == 0)
		exit(1);
	if (check_builtins(cmd->content[0]) == 0)
		exe_builtins(cmd, env);
	if (check_builtins(cmd->content[0]) != 0)
	{
		absolute_path(cmd, envp);
		execute_cmd(cmd, *env, envp);
	}
	exit(0);
}

int	exe_cmds(t_cmd *cmd, t_env **env, char **envp)
{
	int	pid;
	int	fd[2];

	if (cmd->next)
		pipe(fd);
	signal(SIGINT, sig_int_main);
	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
		exe_cmd(cmd, env, envp, fd);
	if (cmd->next)
		ft_pipe2(fd);
	else
		close(0);
	return (pid);
}

void	execution_base(t_cmd *cmd, t_env **env, char **envp)
{
	int		save_in;
	t_cmd	*tmp;
	int		status;
	int		pid;

	pid = 0;
	tmp = cmd;
	save_in = dup(0);
	if (!cmd->next && check_builtins(cmd->content[0]) == 0)
	{
		exe_builtins(cmd, env);
		cmd = cmd->next;
		return ;
	}
	while (cmd)
	{
		pid = exe_cmds(cmd, env, envp);
		cmd = cmd->next;
	}
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	g_exit_status = exit_status(status);
	dup2(save_in, 0);
}
