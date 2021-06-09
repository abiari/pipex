/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:40:49 by abiari            #+#    #+#             */
/*   Updated: 2021/05/06 12:24:03 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*str;

	if (size == 0)
	{
		n = 1;
		size = 1;
	}
	str = malloc(n * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, n * size);
	return (str);
}
