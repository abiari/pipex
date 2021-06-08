/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:52:49 by abiari            #+#    #+#             */
/*   Updated: 2021/05/06 12:29:52 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *str1, const void *str2, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dest;
	unsigned char	*src;
	unsigned char	s;

	s = (unsigned char)c;
	src = (unsigned char *)str2;
	dest = (unsigned char *)str1;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		if (src[i] == s)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
