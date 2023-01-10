/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_st_nd_signls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:42:05 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 20:42:29 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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