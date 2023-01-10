/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 14:47:47 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 20:32:19 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*al;
	size_t	i;
	size_t	j;

	al = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (al == 0)
		return (0);
	i = 0;
	j = 0;
	while (i <= ft_strlen(s1) + ft_strlen(s2))
	{
		while (i < ft_strlen(s1))
		{
			al[i] = s1[i];
			i++;
		}
		al[i] = s2[j];
		i++;
		j++;
	}
	al[i] = '\0';
	return (al);
}
