/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:53:11 by abiari            #+#    #+#             */
/*   Updated: 2021/05/16 13:22:59 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1)
		return (NULL);
	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ret == NULL)
		return (ret);
	i = -1;
	while (s1[++i])
	{
		ret[i] = s1[i];
	}
	j = -1;
	while (s2[++j])
	{
		ret[i] = s2[j];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
