/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 17:38:04 by abiari            #+#    #+#             */
/*   Updated: 2021/06/15 20:41:56 by abiari           ###   ########.fr       */
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

char	*loop_path(char **split_path, char *cmd)
{
	char	*path;
	int		bin_fd;
	int		i;

	i = 0;
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
	free(split_path);
	return (cmd);
}

char	*bin_path(char *cmd, t_data *line, t_list *envl)
{
	char	**split_path;
	int		i;
	t_envl	*path;

	i = 0;
	path = find_env_var("PATH", &envl);
	if (!path)
	{
		line->nopath = 1;
		return (cmd);
	}
	split_path = ft_split(path->value, ':');
	if (!split_path)
	{
		line->nopath = 1;
		return (cmd);
	}
	return (loop_path(split_path, cmd));
}

char	*check_exec(char *cmd, t_data *line, t_list *envl)
{
	char	*bin;
	int		fd;

	bin = cmd;
	if (bin[0] == '\0')
		return (bin);
	fd = open(bin, O_RDONLY);
	if (fd < 0)
		bin = bin_path(bin, line, envl);
	close(fd);
	return (bin);
}
