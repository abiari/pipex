/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:52:13 by abiari            #+#    #+#             */
/*   Updated: 2021/06/15 20:08:31 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	spawn_proc(int in, int *fd, t_data *line, char *envp[])
{
	if (fork() == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (fd[1] != 1)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		if (fd[0] > 2)
			close(fd[0]);
		execve(line->cmds[line->i][0],
			(char *const *)line->cmds[line->i], envp);
		if (errno == ENOENT && line->nopath != 1)
			ft_putendl_fd("Command not found", 2);
		else
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
}

void	spawn_lastcmd(int in, t_data *line, int *fd, char **envp)
{
	int	file;

	line->pid = fork();
	if (line->pid == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (fd[1] > 2)
			close(fd[1]);
		file = open(line->outfile, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (file < 0)
		{
			ft_putendl_fd(strerror(errno), 2);
			exit(1);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
		execve(line->cmds[line->i][0],
			(char *const *)line->cmds[line->i], envp);
		ft_err(line);
	}
}

void	loop_pipes(t_data *line, int *fd, int *in, char **envp)
{
	while (line->cmds[line->i + 1] != NULL)
	{
		if (line->i == 0)
			heredoc_helper(line, in, envp);
		line->bin = line->cmds[line->i][0];
		line->cmds[line->i][0] = check_exec(line->cmds[line->i][0],
				line, line->envl);
		if (line->bin != line->cmds[line->i][0])
			free(line->bin);
		pipe(fd);
		spawn_proc(*in, fd, line, envp);
		close(fd[1]);
		if (*in != 0)
			close(*in);
		*in = fd[0];
		line->i++;
	}
}

int	fork_pipes(t_data *line, char **envp)
{
	int		in;
	char	*bin;
	int		fd[2];
	int		status;
	int		ret;

	in = 0;
	ret = 0;
	line->i = 0;
	loop_pipes(line, fd, &in, envp);
	bin = line->cmds[line->i][0];
	line->cmds[line->i][0] = check_exec(line->cmds[line->i][0],
			line, line->envl);
	if (bin != line->cmds[line->i][0])
		free(bin);
	if (line->cmds[line->i][0] == NULL)
		exit(127);
	spawn_lastcmd(in, line, fd, envp);
	if (in != 0)
		close(in);
	wait_procs(&ret, &status, line);
	return (ret);
}
