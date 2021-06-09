/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 09:20:38 by abiari            #+#    #+#             */
/*   Updated: 2021/05/06 12:37:55 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;

	if (!h && !n && !len)
		ft_strlen(h);
	if (*n == '\0')
		return ((char *)h);
	i = ft_strlen(n);
	while (*h != '\0' && len >= i)
	{
		if (ft_strncmp(h, n, i) == 0)
			return ((char *)h);
		h++;
		len--;
	}
	return (NULL);
}
