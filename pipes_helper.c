/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:28:34 by abiari            #+#    #+#             */
/*   Updated: 2021/06/12 14:02:56 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int *in, t_data *line)
{
	*in = open(line->infile, O_RDONLY);
	if (*in < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		write(2, "\n", 1);
		exit(1);
	}
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
