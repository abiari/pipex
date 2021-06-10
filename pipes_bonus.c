/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 09:52:13 by abiari            #+#    #+#             */
/*   Updated: 2021/06/10 11:51:05 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	spawn_proc(int in, int *fd, char **cmd, char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
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
		execve(cmd[0], (char *const *)cmd, envp);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		write(2, "\n", 1);
		exit(errno);
	}
}

void	spawn_lastcmd(int in, t_data *line, int *fd, char **envp)
{
	int	file;

	if (fork() == 0)
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
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
}

void	pipes_exit(char *bin)
{
	if (bin == NULL)
		exit (1);
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
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
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

void	loop_pipes(t_data *line, int *fd, int *in, char **envp)
{
	while (line->cmds[line->i + 1] != NULL)
	{
		if (line->i == 0)
			heredoc_helper(line, in, envp);
		line->bin = line->cmds[line->i][0];
		line->cmds[line->i][0] = check_exec(line->cmds[line->i][0], line->envl);
		if (line->bin != line->cmds[line->i][0])
			free(line->bin);
		pipes_exit(line->cmds[line->i][0]);
		pipe(fd);
		spawn_proc(*in, fd, line->cmds[line->i], envp);
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
	line->cmds[line->i][0] = check_exec(line->cmds[line->i][0], line->envl);
	if (bin != line->cmds[line->i][0])
		free(bin);
	if (line->cmds[line->i][0] == NULL)
		exit(127);
	spawn_lastcmd(in, line, fd, envp);
	if (in != 0)
		close(in);
	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) != 0)
				ret = WEXITSTATUS(status);
	return (ret);
}
