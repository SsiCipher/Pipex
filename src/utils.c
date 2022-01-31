/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 02:01:33 by yanab             #+#    #+#             */
/*   Updated: 2022/01/31 11:58:34 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(EXIT_FAILURE);
}

char	**get_env_paths(char **envp)
{
	int		i;
	char	*path_ptr;
	char	**split_path;

	i = -1;
	while (envp[++i])
	{
		if (ft_strstr(envp[i], "PATH="))
		{
			path_ptr = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			split_path = ft_split(path_ptr, ':');
			free(path_ptr);
			return (split_path);
		}
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd_name, char **envp)
{
	int		i;
	char	**split_paths;
	char	*tmp;
	char	*cmd_path;

	split_paths = get_env_paths(envp);
	if (!split_paths)
		print_error("Error: Can't get PATH environment variable\n");
	i = -1;
	while (split_paths[++i])
	{
		cmd_path = ft_strjoin(split_paths[i], "/");
		tmp = cmd_path;
		cmd_path = ft_strjoin(cmd_path, cmd_name);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
			free(cmd_path);
	}
	return (NULL);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**split_cmd;
	int		cmd_exec;

	split_cmd = ft_split(cmd, ' ');
	cmd_exec = execve(get_cmd_path(split_cmd[0], envp), split_cmd, envp);
	if (cmd_exec == -1)
		print_error("Error: Command not found\n");
	exit(EXIT_SUCCESS);
}
