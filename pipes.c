/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:52:13 by abiari            #+#    #+#             */
/*   Updated: 2021/06/10 11:48:55 by abiari           ###   ########.fr       */
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
		exit(errno);
	}
}

void	spawn_proc(int in, int *fd, t_data *line, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (line->i == 0)
			print_error(&in, line);
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
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		write(2, "\n", 1);
		exit(errno);
	}
}

void	spawn_lastcmd(int in, t_data *line, int *fd, char **envp)
{
	int		file;

	if (fork() == 0)
	{
		file = open(line->outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (file < 0)
		{
			ft_putendl_fd(strerror(errno), 2);
			exit(1);
		}
		if (fd[1] > 2)
			close(fd[1]);
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		dup2(file, STDOUT_FILENO);
		close(file);
		execve(line->cmds[line->i][0],
			(char *const *)line->cmds[line->i], envp);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
}

void	pipes_exit(char *bin)
{
	if (bin == NULL)
		exit (127);
}

void	loop_pipes(t_data *line, int *fd, int *in, char **envp)
{
	while (line->cmds[line->i + 1] != NULL)
	{
		line->bin = line->cmds[line->i][0];
		line->cmds[line->i][0] = check_exec(line->cmds[line->i][0], line->envl);
		if (line->bin != line->cmds[line->i][0])
			free(line->bin);
		pipes_exit(line->cmds[line->i][0]);
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

	ret = 0;
	in = 0;
	line->i = 0;
	loop_pipes(line, fd, &in, envp);
	bin = line->cmds[line->i][0];
	line->cmds[line->i][0] = check_exec(line->cmds[line->i][0], line->envl);
	if (bin != line->cmds[line->i][0])
		free(bin);
	if (line->cmds[line->i][0] == NULL)
		exit (127);
	spawn_lastcmd(in, line, fd, envp);
	if (in != 0)
		close(in);
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) != 0)
				ret = WEXITSTATUS(status);
	return (ret);
}
