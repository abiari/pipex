/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:26:20 by abiari            #+#    #+#             */
/*   Updated: 2021/06/16 10:39:44 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			if (line->cmds[i][j])
				free(line->cmds[i][j]);
			line->cmds[i][j] = NULL;
			j++;
		}
		if (line->cmds[i])
			free(line->cmds[i]);
		line->cmds[i] = NULL;
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
		if (cmds[i][0] == NULL)
		{
			free(cmds[i]);
			cmds[i] = (char **)malloc(sizeof(char *) * 2);
			cmds[i][0] = ft_strdup("");
			cmds[i][1] = NULL;
		}
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
	int		ret;

	(void)envp;
	ret = 0;
	if (argc != 5)
	{
		ft_putstr_fd("error argument\n", 2);
		return (1);
	}
	line = init_line(argc, argv, envp);
	ret = fork_pipes(line, envp);
	ft_free(line);
	return (ret);
}
