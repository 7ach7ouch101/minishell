#include "../minishell.h"

void    ft_pipe(int fd[])
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

int exe_builtins(t_cmd *cmd, t_env *env)
{
    if(ft_strcmpp(cmd->content[0], "echo") == 0)
        ft_echo(cmd->content);
    else if(ft_strcmpp(cmd->content[0], "env") == 0)
        ft_env(cmd->content, env);
    else if(ft_strcmpp(cmd->content[0], "cd") == 0)
        ft_cd(cmd->content, env);
    else if(ft_strcmpp(cmd->content[0], "pwd") == 0)
        ft_pwd();
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
    return (1);
}

void    redirections(t_red *red)
{
    int fd;

    fd = 0;
    if(red->type == APPAND)
    {
        fd = open(red->file_name, O_APPEND | O_CREAT | O_WRONLY, 0666);
        dup2(fd, 1);
        close(fd);
    }
    if(red->type == OUTFILE)
    {
        fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(fd, 1);
        close(fd);
    }
    if(red->type == INFILE)
    {
        fd = open(red->file_name, O_RDONLY);
        if(fd < 0)
        {
            printf("%s: No such file or directory\n", red->file_name);
            return ;
        }
        dup2(fd, 0);
        close(fd);
    }
}
void    execute_cmd(t_cmd *cmd, t_env *env, char **envp)
{
    char **str;
    char *tmp;
    int i;

    i = 0;
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
                    if(execve(tmp, cmd->content, envp) < 0)
                        printf("%s: command not found\n", tmp);
                }   
                free(tmp);
            }
        }
        env = env->next;
    }
    printf("%s: command not found\n", cmd->content[0]);
}
void    exe_cmds(t_cmd *cmd, t_env *env, char **envp)
{
    int pid;
    int fd[2];

    if(cmd->next)
        pipe(fd);
    pid = fork();
    if(pid < 0)
        return ;
    if(pid == 0)
    {
        if(cmd->next)
            ft_pipe(fd);
        if(check_builtins(cmd->content[0]) == 0)
        {
            exe_builtins(cmd, env);
            exit(0);
        }
        execute_cmd(cmd, env, envp);
        exit(0);
    }
    if(cmd->next)
        ft_pipe2(fd);
    else
    {
        close(0);
    }
    waitpid(-1, NULL, 0);
}

void    execution_base(t_cmd *cmd, t_env *env, char **envp)
{
    int fd[2];
    int save_in;

    save_in = dup(0);
    fd[0] = dup(0);
	fd[1] = dup(1);
    while(1)
    {
        if(cmd->red)
            redirections(cmd->red);
        exe_cmds(cmd, env, envp);
        if(cmd->red)
        {
            dup2(fd[1], 1);
            dup2(fd[0], 0);
            close(fd[1]);
            close(fd[0]);
        }
        if(cmd->next == NULL)
           break ;
        cmd = cmd->next;
    }
    dup2(save_in, 0);
}