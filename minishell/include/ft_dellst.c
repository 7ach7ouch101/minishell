/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dellst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:16:51 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/06/23 15:16:17 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
extern int	g_exit_status;
void	ft_dellst(t_list **lst, t_list *del)
{
	(*lst)->next = (*lst)->next->next;
	ft_lstdelone((del), free);
}
