/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dellst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:16:51 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 20:33:15 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dellst(t_list **lst, t_list *del)
{
	(*lst)->next = (*lst)->next->next;
	ft_lstdelone((del), free);
}
