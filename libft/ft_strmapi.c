/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:11:01 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 22:03:01 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ml;
	int		i;

	if (!s)
		return (0);
	ml = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (ml == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		ml[i] = f(i, s[i]);
		i++;
	}
	ml[i] = '\0';
	return (ml);
}
