/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 21:05:33 by abiari            #+#    #+#             */
/*   Updated: 2021/06/08 18:19:16 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	findset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		slen;
	int		srt;
	int		end;
	char	*p;

	srt = 0;
	end = 0;
	if (!s1 || !set)
		return (NULL);
	slen = ft_strlen(s1);
	while (findset(s1[srt], set))
		srt++;
	while (findset(s1[slen - 1 - end], set))
		end++;
	if ((srt + end) >= slen)
	{
		p = (char *)malloc(1);
		*p = '\0';
		return (p);
	}
	return (ft_substr(s1, srt, slen - end - srt));
}
