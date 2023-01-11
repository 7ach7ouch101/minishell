/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:54:59 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 20:54:59 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(char **str, t_env *env)
{
	g_exit_status = 0;
	if (!str[1])
	{
		while (env)
		{
			if (env && env->content && ((ft_strcmp(env->name, "PATH"))
					|| (!ft_strcmp(env->name, "PATH")
						&& ft_strncmp(env->content, "d:", 2))))
				printf("%s=%s\n", env->name, env->content);
			env = env->next;
		}
	}
	else
	{
		printf("env: no arguments needed here\n");
		g_exit_status = 1;
	}
}
