/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:29:52 by abiari            #+#    #+#             */
/*   Updated: 2021/06/16 11:20:40 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_err(t_data *line)
{
	if (errno == ENOENT && line->nopath != 1)
	{
		ft_putendl_fd("Command not found", 2);
		exit(127);
	}
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(errno);
}

void	heredoc(t_data *data, int fd)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		if (get_next_line(0, &line) <= 0)
			break ;
		if (!ft_strcmp(line, data->infile))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	remove_tmp(char **envp)
{
	char	*rm[4];

	if (fork() == 0)
	{
		rm[0] = ft_strdup("/bin/rm");
		rm[1] = ft_strdup("-rf");
		rm[1] = ft_strdup("/tmp/heredoctmpfile");
		rm[2] = NULL;
		execve(rm[0], rm, envp);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
}

void	heredoc_helper(t_data *line, int *in, char **envp)
{
	int	file;

	file = open("/tmp/heredoctmpfile", O_CREAT | O_TRUNC | O_WRONLY,
			S_IRGRP | S_IWGRP | S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
	if (file < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		exit(errno);
	}
	heredoc(line, file);
	close(file);
	file = open("/tmp/heredoctmpfile", O_RDONLY);
	remove_tmp(envp);
	*in = file;
}

void	wait_procs(int *ret, int *status, t_data *line)
{
	pid_t	test;

	while (1)
	{
		test = waitpid(-1, status, 0);
		if (test <= 0)
			break ;
		else
		{
			if (test == line->pid)
				if (WIFEXITED(*status))
					if (WEXITSTATUS(*status) != 0)
						*ret = WEXITSTATUS(*status);
		}
	}
}
