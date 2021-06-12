/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:11:53 by abiari            #+#    #+#             */
/*   Updated: 2021/06/10 15:54:40 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stock(int fd, char *str)
{
	char	*temp;
	int		b_read;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	b_read = 0;
	if (!str)
		str = ft_strdup("");
	while (ft_strchr(str, '\n') == NULL)
	{
		b_read = read(fd, buff, BUFFER_SIZE);
		if ((b_read) < 0)
		{
			free(buff);
			return (0);
		}
		buff[b_read] = '\0';
		temp = str;
		str = ft_strjoin(str, buff);
		free(temp);
		if (b_read == 0 || str[0] == '\0')
			break ;
	}
	free(buff);
	return (str);
}

int	exit_nonewline(char *line, char *str)
{
	line = ft_strdup(str);
	if (!(line))
		return (-1);
	free(str);
	str = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		*temp;
	char		c;

	if (fd < 0 || !line || read(fd, &c, 0))
		return (-1);
	str = ft_stock(fd, str);
	if ((str) == NULL)
		return (0);
	if (!(ft_strchr(str, '\n')))
		return (exit_nonewline(*line, str));
	else
	{
		temp = str;
		*line = ft_substr(str, 0, (ft_strchr(str, '\n') - str));
		str = ft_strdup(str + (ft_strchr(str, '\n') - str) + 1);
		free(temp);
		return (1);
	}
}
