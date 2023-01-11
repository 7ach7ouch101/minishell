/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:54:56 by mmeziani          #+#    #+#             */
/*   Updated: 2023/01/10 20:54:56 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char **str)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	while (ft_ncmp(str[i]) == 0)
	{
		check ++;
		i++;
	}
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
	}
	if (!check)
		printf("\n");
	g_exit_status = 0;
	return ;
}
