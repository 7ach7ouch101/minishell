/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:20:16 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 20:33:21 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstinsert(t_list **lst, t_list *new)
{
	(new)->next = (*lst)->next;
	(*lst)->next = (new);
}
