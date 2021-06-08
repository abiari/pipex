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
}				t_data;

typedef struct s_procs
{
	int		in;
	int		fd[2];
	char	*bin;
	pid_t	pid;
	int		file;
}				t_procs;

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
#endif
