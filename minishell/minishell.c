/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:42:55 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/09 01:29:31 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	check_line(char *buff, t_env **env, char **envp)
{
	t_list	*arg;
	t_cmd	*cmd;

	arg = NULL;
	if (buff[0])
	{
		add_history(buff);
		if (lex(buff, &arg, *env) || only_space(arg))
			ft_lstclear(&arg, free);
		else
		{
			ft_wildcard(&arg);
			cmd = split_pipe(arg);
			redirections_parser(cmd);
			execution_base(cmd, env, envp);
			signal(SIGINT, handler);
			ft_lstclear(&arg, free);
			ft_cmdclear(&cmd, free);
		}
	}
}

void	handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 1;
}

int	main(int ac, char **av, char **envp)
{
	char	*buff;
	t_env	*env;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	ac = 0;
	av = NULL;
	env = create_list(envp);
	while (1)
	{
		buff = readline("minishell:~$ ");
		if (!buff)
		{
			//ft_free_env(env);
			printf("exit\n");
			exit(0);
		}
		check_line(buff, &env, envp);
		free(buff);
	}
	return (0);
}
