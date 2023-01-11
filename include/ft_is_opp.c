/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_opp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:37:45 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 20:33:19 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_opp(t_list *arg)
{
	if (ft_strcmp(arg->content, "<<") == 0
		|| ft_strcmp(arg->content, ">>") == 0
		|| ft_strcmp(arg->content, "|") == 0
		|| ft_strcmp(arg->content, "<") == 0
		|| ft_strcmp(arg->content, ">") == 0)
		return (1);
	return (0);
}
