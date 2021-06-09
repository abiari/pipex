/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:26:20 by abiari            #+#    #+#             */
/*   Updated: 2021/06/09 10:01:57 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	ft_lstclear(&line->envl, &envl_clear);
	free(line->envl);
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

t_data	*init_line(int argc, char *argv[], char **envp)
{
	char	**raw_cmds;
	t_data	*line;

	line = (t_data *)malloc((sizeof(t_data)));
	line->cmds = (char ***)malloc(sizeof(char **) * argc - 2);
	raw_cmds = (char **)malloc(sizeof(char *) * argc - 2);
	line->infile = ft_strdup(argv[1]);
	line->outfile = ft_strdup(argv[argc - 1]);
	line->envl = envp_to_envl(envp);
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
	line = init_line(argc, argv, envp);
	fork_pipes(line, envp);
	ft_free(line);
	return (0);
}