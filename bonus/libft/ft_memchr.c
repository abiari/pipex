/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:10:01 by abiari            #+#    #+#             */
/*   Updated: 2021/05/06 12:29:58 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int ch, size_t lenght)
{
	unsigned int	i;
	char			*string;

	string = (char *)buf;
	i = 0;
	while (i < lenght)
	{
		if (string[i] == ch)
			return (&string[i]);
		i++;
	}
	return (NULL);
}
