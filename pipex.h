#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"

typedef struct s_envl
{
	char	*key;
	char	*value;
	char	*var;
	int		env_printable;
}				t_envl;

typedef struct s_data
{
	char	***cmds;
	char	*infile;
	char	*outfile;
	int		i;
	t_list	*envl;
	char	*bin;
}				t_data;

char	*find_env_key(const char *envp);
char	*find_env_value(const char *envp);
t_list	*envp_to_envl(char *envp[]);
void	lst_append(t_list **lst, void *content);
void	mod_env_var(char *var, char *new_value, t_list **envl);
void	add_env_var(char *var, char *value, t_list **envl);
void	envl_clear(void *content);
int		delete_env_var(char *var, t_list **envl);
t_envl	*find_env_var(char *var, t_list **envl);
char	*bin_path(char *cmd, t_list *envl);
char	*check_exec(char *cmd, t_list *envl);
int		fork_pipes(t_data *line, char **envp);
void	loop_pipes(t_data *line, int *fd, int *in, char **envp);
void	spawn_lastcmd(int in, t_data *line, int *fd, char **envp);
void	spawn_proc(int in, int *fd, t_data *line, char *envp[]);
#endif
