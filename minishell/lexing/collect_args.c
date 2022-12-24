/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:12:14 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/09/02 01:10:14 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
extern int	g_exit_status;
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
