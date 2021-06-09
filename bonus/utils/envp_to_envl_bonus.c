/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_envl_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:28:27 by abiari            #+#    #+#             */
/*   Updated: 2021/06/09 10:02:08 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*find_env_key(const char *envp)
{
	int	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
	{
		len++;
	}
	return (ft_substr(envp, 0, len));
}

char	*find_env_value(const char *envp)
{
	char	*value;

	value = ft_strchr(envp, '=') + 1;
	return (value);
}

t_list	*envp_to_envl(char *envp[])
{
	int		i;
	t_list	*envl;
	t_envl	*env;

	i = 0;
	envl = NULL;
	while (envp[i] != NULL)
	{
		env = malloc(sizeof(t_envl));
		if (env == NULL)
		{
			printf("msh: %s", strerror(errno));
			exit(errno);
		}
		env->value = ft_strdup(find_env_value(envp[i]));
		env->var = ft_strdup(envp[i]);
		env->key = find_env_key(envp[i]);
		lst_append(&envl, env);
		i++;
	}
	return (envl);
}
