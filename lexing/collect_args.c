/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:12:14 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 20:32:45 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	collect_args(char *buff, t_lex *lex, t_list **arg)
{
	int	i;

	i = 0;
	while (buff[lex->i] && buff[lex->i] != '\''
		&& buff[lex->i] != '"' && buff[lex->i] != ' ')
	{
		if (i++ == 0)
			lex->argstart = lex->i;
		lex->i++;
	}
	lex->arglen = lex->i;
	if (i > 0)
		ft_lstadd_back(arg,
			ft_lstnew(ft_substr_lex(buff, lex->argstart, lex->arglen), 0));
}
