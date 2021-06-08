/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:26:20 by abiari            #+#    #+#             */
/*   Updated: 2021/06/08 18:09:26 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	fork_pipes(t_data *line, char **envp)
{
	int		in;
	char	*bin;
	pid_t	pid;
	int		file;
	int		fd[2];
	int		i;
	t_list	*tmp;

	in = 0;
	i = 0;
	tmp = envp_to_envl(envp);
	while (line->cmds[i + 1] != NULL)
	{
		if (i == 0)
		{
			in = open(line->infile, O_RDONLY);
			if (in < 0)
			{
				ft_putstr_fd(strerror(errno), 2);
				write(2, "\n", 1);
				exit(errno);
			}
		}
		bin = line->cmds[i][0];
		line->cmds[i][0] = check_exec(line->cmds[i][0], tmp);
		free(bin);
		if (line->cmds[i][0] == NULL)
			return ;
		pipe(fd);
		spawn_proc(in, fd, line->cmds[i], envp);
		close(fd[1]);
		if (in != 0)
			close(in);
		in = fd[0];
		i++;
	}
	bin = line->cmds[i][0];
	line->cmds[i][0] = check_exec(line->cmds[i][0], tmp);
	free(bin);
	if (line->cmds[i][0] == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (fd[1] > 2)
			close(fd[1]);
		file = open(line->outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		dup2(file, STDOUT_FILENO);
		close(file);
		execve(line->cmds[i][0], (char *const *)line->cmds[i], envp);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		exit(errno);
	}
	if (in != 0)
		close(in);
	while (waitpid(-1, NULL, 0) > 0)
		;
	ft_lstclear(&tmp, &envl_clear);
	free(tmp);
}

void	ft_free(t_data *line)
{
	int	i;
	int	j;

	i = 0;
	while (line->cmds[i])
	{
		j = 0;
		while (line->cmds[i][j])
		{
			free(line->cmds[i][j]);
			j++;
		}
		free(line->cmds[i]);
		i++;
	}
	free(line->cmds);
	free(line->infile);
	free(line->outfile);
}

void	fill_it(char **raw_cmds, char ***cmds, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc - 3)
	{
		raw_cmds[i] = ft_strdup(argv[i + 2]);
		i++;
	}
	raw_cmds[i] = NULL;
	i = 0;
	while (raw_cmds[i])
	{
		cmds[i] = ft_split(raw_cmds[i], ' ');
		free(raw_cmds[i]);
		i++;
	}
	cmds[i] = NULL;
	free(raw_cmds);
}

t_data	*init_line(int argc, char *argv[])
{
	char	**raw_cmds;
	t_data	*line;

	line = (t_data *)malloc((sizeof(t_data)));
	line->cmds = (char ***)malloc(sizeof(char **) * argc - 2);
	raw_cmds = (char **)malloc(sizeof(char *) * argc - 2);
	line->infile = ft_strdup(argv[1]);
	line->outfile = ft_strdup(argv[argc - 1]);
	fill_it(raw_cmds, line->cmds, argc, argv);
	return (line);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	*line;

	(void)envp;
	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	line = init_line(argc, argv);
	fork_pipes(line, envp);
	ft_free(line);
	// while (1);
	return (0);
}
