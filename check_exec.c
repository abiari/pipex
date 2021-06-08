/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:38:04 by abiari            #+#    #+#             */
/*   Updated: 2021/06/08 17:38:58 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double(char **arr, int i)
{
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*bin_path(char *cmd, t_list *envl)
{
	char	**split_path;
	char	*path;
	int		bin_fd;
	int		i;

	i = 0;
	split_path = ft_split((find_env_var("PATH", &envl))->value, ':');
	if (!split_path)
	{
		ft_putstr_fd("msh: No such file or directory", 2);
		return (NULL);
	}
	while (split_path[i])
	{
		path = split_path[i];
		split_path[i] = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(split_path[i], cmd);
		free(split_path[i]);
		bin_fd = open(path, O_RDONLY);
		if (bin_fd > 0)
		{
			free_double(split_path, i + 1);
			close(bin_fd);
			return (path);
		}
		free(path);
		i++;
	}
	ft_putstr_fd("msh: command not found", 2);
	free(split_path);
	return (NULL);
}

char	*check_exec(char *cmd, t_list *envl)
{
	char	*bin;
	int		fd;

	bin = cmd;
	fd = open(bin, O_RDONLY);
	if (fd < 0)
	{
		bin = bin_path(bin, envl);
		close(fd);
	}
	return (bin);
}
