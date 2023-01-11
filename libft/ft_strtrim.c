/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:48:35 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 22:04:30 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ml;
	int		i;
	int		j;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	j = ft_strlen((char *)s1);
	while (j >= 0 && ft_strlen((char *)set) > 0)
	{
		if (ft_strrchr(set, s1[j]) == 0)
			break ;
		j--;
	}
	ml = ft_substr(s1, i, j + 1 - i);
	if (ml == 0)
		return (0);
	return (ml);
}
