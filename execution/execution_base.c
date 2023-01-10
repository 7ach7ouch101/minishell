#include "../minishell.h"

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WTERMSIG(status) != SIGINT)
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3\n");
	}
	return (128 + WTERMSIG(status));
}

void	ft_pipe(int fd[])
{
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
}
void    ft_pipe2(int fd[])
{
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}

int	redirections(t_red *red)
{
	int fd;

	fd = 0;
	if(red->type == APPAND)
	{
		fd = open(red->file_name, O_APPEND | O_CREAT | O_WRONLY, 0666);
		if(fd < 0)
			return (0);
		dup2(fd, 1);
		close(fd);
	}
	if(red->type == OUTFILE)
	{
		fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if(fd < 0)
			return (0);
		dup2(fd, 1);
		close(fd);
	}
	if(red->type == INFILE)
	{
		fd = open(red->file_name, O_RDONLY);
		if(fd < 0)
			return 0;
		dup2(fd, 0);
		close(fd);
	}
	if(red->type == HERDOC)
	{
		dup2(red->pipe_0, 0);
		close(red->pipe_0);
	}
	return (1);
}

int    red_test(t_red *red)
{
	t_red *tmp;
	tmp = red;
	int save_out;

	save_out = dup(1);
	while(tmp)
	{
		if(redirections(tmp) == 0)
		{
			dup2(save_out, 1);
			printf("%s: No such file or directory\n", tmp->file_name);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void    exe_builtins(t_cmd *cmd, t_env **env)
{
	int fd[2];

	fd[1] = dup(1);
	fd[0] = dup(0);
	if(cmd->red)
		if(red_test(cmd->red) == 0)
			return ;
	if(ft_strcmpp(cmd->content[0], "echo") == 0)
		ft_echo(cmd->content);
	else if(ft_strcmpp(cmd->content[0], "env") == 0)
		ft_env(cmd->content, *env);
	else if(ft_strcmpp(cmd->content[0], "cd") == 0)
		ft_cd(cmd->content, *env);
	else if(ft_strcmpp(cmd->content[0], "pwd") == 0)
		ft_pwd();
	else if(ft_strcmpp(cmd->content[0], "unset") == 0)
		ft_unset(env, cmd);
	else if(ft_strcmpp(cmd->content[0], "export") == 0)
		ft_export(cmd->content, env);
	else if(ft_strcmpp(cmd->content[0], "exit") == 0)
		ft_exit(cmd->content);
	if(cmd->red)
	{
		dup2(fd[1] , 1);
		dup2(fd[0], 0);
	}
}

int check_builtins(char *str)
{
	if(ft_strcmpp(str, "echo") == 0)
		return (0);
	else if(ft_strcmpp(str, "env") == 0)
		return (0);
	else if(ft_strcmpp(str, "cd") == 0)
		return (0);
	else if(ft_strcmpp(str, "pwd") == 0)
		return (0);
	else if(ft_strcmpp(str, "unset") == 0)
		return (0);
	else if(ft_strcmpp(str, "export") == 0)
		return (0);
	else if(ft_strcmpp(str, "exit") == 0)
		return (0);
	return (1);
}
void    execute_cmd(t_cmd *cmd, t_env *env, char **envp)
{
	char **str;
	char *tmp;
	int i;

	i = 0;
	if(!cmd->content[0] || !cmd->content)
		exit(0);
	while(env->next)
	{
		if(ft_strcmpp(env->name, "PATH") == 0)
		{
			str = ft_split(env->content, ':');
			while(str[++i])
			{
				tmp = ft_strjoin(str[i], "/");
				if (access(ft_strjoin(tmp , cmd->content[0]), X_OK) == 0)
				{
					tmp = ft_strjoin(tmp , cmd->content[0]);
					break;
				}   
				free(tmp);
			}
		}
		env = env->next;
	}
   if(execve(tmp, cmd->content, envp) < 0)
		return(printf("%s: command not found\n", cmd->content[0]),exit(127));
}

void    absolute_path(t_cmd *cmd, char **envp)
{
	if(!cmd->content[0] || !cmd->content)
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

void	sig_int(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	sig_int_main(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		printf("\n");
}

int		exe_cmds(t_cmd *cmd, t_env **env, char **envp)
{
	int pid;
	int fd[2];

	if(cmd->next)
		pipe(fd);
	signal(SIGINT, sig_int_main);
	pid = fork();
	if(pid < 0)
		return 0;
	if(pid == 0)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_DFL);
		if(cmd->next)
			ft_pipe(fd);
		if(red_test(cmd->red) == 0)
			exit(1);
		exe_builtins(cmd, env);
		if(check_builtins(cmd->content[0]) != 0)
		{
			absolute_path(cmd, envp);
			execute_cmd(cmd, *env, envp);
		}
		exit(0);
	}
	if(cmd->next)
		ft_pipe2(fd);
	else
		close(0);
	return (pid);
}

void	execution_base(t_cmd *cmd, t_env **env, char **envp)
{
	int save_in;
	t_cmd *tmp;
	int status;
	int pid;

	pid = 0;
	tmp = cmd;
	save_in = dup(0);
	if (!cmd->next && check_builtins(cmd->content[0]) == 0)
	{
		exe_builtins(cmd, env);
		cmd = cmd->next;
		return ;
	}
	while(cmd)
	{
		pid = exe_cmds(cmd, env, envp);
		cmd = cmd->next;
	}
	waitpid(pid, &status, 0);
	while(waitpid(-1, NULL, 0) != -1)
	;
	g_exit_status = exit_status(status);
	dup2(save_in, 0);
}