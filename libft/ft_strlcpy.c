/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:24:27 by ahel-bah          #+#    #+#             */
/*   Updated: 2023/01/10 16:21:56 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlcpy(char **dst, char *src, int dstsize)
{
	int	i;
	int	srcsize;

	i = 0;
	(*dst) = malloc((dstsize + 1) * sizeof(char));
	if (dstsize == 0)
		return (NULL);
	while (src[i] != '\0' && i < dstsize)
	{
		(*dst)[i] = src[i];
		i++;
	}
	(*dst)[i] = '\0';
	return (*dst);
}
