/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 02:01:26 by cipher            #+#    #+#             */
/*   Updated: 2022/06/04 20:03:28 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_start_cmds(int cmd_i, int *pipe_ends, char **argv, char **envp)
{
	int	infile_fd;

	if (cmd_i == 0)
	{
		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd == -1)
			print_error("Error: Failed to open infile\n", NULL);
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
	}
	close(pipe_ends[READ_END]);
	dup2(pipe_ends[WRITE_END], STDOUT_FILENO);
	close(pipe_ends[WRITE_END]);
	execute_cmd(argv[cmd_i + 2], envp);
}

void	exec_cmd_in_proc(int cmd_i, int *pipe_ends, char **argv, char **envp)
{
	pid_t	cmd_proc_pid;

	cmd_proc_pid = fork();
	if (cmd_proc_pid == -1)
		print_error("Error: The fork function failed\n", NULL);
	else if (cmd_proc_pid == 0)
		exec_start_cmds(cmd_i, pipe_ends, argv, envp);
	else
	{
		close(pipe_ends[WRITE_END]);
		dup2(pipe_ends[READ_END], STDIN_FILENO);
		close(pipe_ends[READ_END]);
		pipe(pipe_ends);
	}
}

void	exec_last_cmd(char *outfile_name, char *cmd, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC, 00666);
	if (outfile_fd == -1)
		print_error("Error: Failed to open outfile\n", NULL);
	dup2(outfile_fd, 1);
	close(outfile_fd);
	execute_cmd(cmd, envp);
}
