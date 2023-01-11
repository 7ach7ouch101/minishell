/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:55:09 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 20:55:09 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(void)
{
	char	cwd[1000];

	g_exit_status = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("pwd: Error occurred.\n");
		g_exit_status = 1;
	}
	else
		printf("%s\n", cwd);
}
