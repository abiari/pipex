/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 06:39:30 by abiari            #+#    #+#             */
/*   Updated: 2019/10/23 18:00:08 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	if (n > 0)
	{
		ft_memccpy(dst, src, '\0', n - 1);
		*(dst + n - 1) = '\0';
	}
	return (ft_strlen(src));
}
