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
    if(red->type == HERDOC)
    {
        dup2(red->pipe_0, 0);
        close(red->pipe_0);
    }
}

void    red_test(t_red *red)
{
    t_red *tmp;
    tmp = red;

    while(tmp)
    {
        redirections(tmp);
        tmp = tmp->next;
    }
    return ;
}

void    exe_builtins(t_cmd *cmd, t_env *env)
{
    int fd[2];

    fd[1] = dup(1);
    fd[0] = dup(0);
    if(cmd->red)
        red_test(cmd->red);
    if(ft_strcmpp(cmd->content[0], "echo") == 0)
        ft_echo(cmd->content);
    else if(ft_strcmpp(cmd->content[0], "env") == 0)
        ft_env(cmd->content, env);
    else if(ft_strcmpp(cmd->content[0], "cd") == 0)
        ft_cd(cmd->content, env);
    else if(ft_strcmpp(cmd->content[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmpp(cmd->content[0], "unset") == 0)
        ft_unset(&env, cmd);
    else if(ft_strcmpp(cmd->content[0], "export") == 0)
        ft_export(cmd->content, env);
    dup2(fd[1] , 1);
    dup2(fd[0], 0);
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
        printf("%s: command not found\n", cmd->content[0]);
}

void    absolute_path(t_cmd *cmd, char **envp)
{
    if(!cmd->content[0] || !cmd->content)
        exit(0);
    if (access(cmd->content[0], X_OK) == 0)
    {
        if (execve(cmd->content[0], cmd->content, envp) < 0)
            printf("%s: command not found\n", cmd->content[0]);
    }
}

void    exe_cmds(t_cmd *cmd, t_env *env, char **envp)
{
    int pid;
    int fd[2];

    if (!cmd->next && check_builtins(cmd->content[0]) == 0)
    {
        //red_test(cmd->red);
        exe_builtins(cmd, env);
    }
    else
    {
        if(cmd->next)
            pipe(fd);
        pid = fork();
        if(pid < 0)
            return ;
        if(pid == 0)
        {
            if(cmd->next)
                ft_pipe(fd);
            red_test(cmd->red);
            exe_builtins(cmd, env);
            if(check_builtins(cmd->content[0]) != 0)
            {
                absolute_path(cmd, envp);
                execute_cmd(cmd, env, envp);
            }
            exit(0);
        }
        if(cmd->next)
            ft_pipe2(fd);
        else
            close(0);
    }
}

void    execution_base(t_cmd *cmd, t_env *env, char **envp)
{
    int save_in;
    t_cmd *tmp;

    tmp = cmd;
    save_in = dup(0);

    while(cmd)
    {
        exe_cmds(cmd, env, envp);
        cmd = cmd->next;
    }
    while(tmp)
    {
        wait(NULL);
        tmp = tmp->next;
    }
    dup2(save_in, 0);
}