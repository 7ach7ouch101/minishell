/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:18:18 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 20:47:58 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	herdoc(t_red *red)
{
	dup2(red->pipe_0, 0);
	close(red->pipe_0);
}

int	redirections(t_red *red)
{
	int fd;

	fd = 0;
	if(red->type == OUTFILE || red->type == APPAND)
	{
        if(red->type == OUTFILE)
		    fd = open(red->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        else
            fd = open(red->file_name, O_APPEND | O_CREAT | O_WRONLY, 0666);
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
		herdoc(red);
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