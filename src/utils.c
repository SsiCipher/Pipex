/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 02:01:33 by yanab             #+#    #+#             */
/*   Updated: 2022/06/03 02:05:04 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *error_msg, char *arg)
{
	if (arg)
		error_msg = ft_strjoin(error_msg, arg);
	ft_putstr_fd(error_msg, 2);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	print_sys_error(char *arg)
{
	char	*error;
	char	*tmp;

	error = ft_strjoin("Error: ", strerror(errno));
	tmp = error;
	error = ft_strjoin(error, ": ");
	free(tmp);
	tmp = error;
	error = ft_strjoin(error, arg);
	free(tmp);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
	free(error);
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
		if (ft_strnstr(envp[i], "PATH=", 5))
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
		print_error("Error: Can't get PATH environment variable", NULL);
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
	int		i;
	int		cmd_exec;
	char	**split_cmd;
	char	*temp;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		print_error("Error: ft_split failed", NULL);
	i = -1;
	while (split_cmd[++i])
	{
		temp = split_cmd[i];
		split_cmd[i] = ft_strtrim(split_cmd[i], "'\"");
		free(temp);
	}
	if (!ft_strchr(split_cmd[0], '/'))
		cmd_exec = execve(get_cmd_path(split_cmd[0], envp), split_cmd, envp);
	else
		cmd_exec = execve(split_cmd[0], split_cmd, envp);
	if (cmd_exec == -1)
		print_error("Error: Command not found: ", split_cmd[0]);
}
