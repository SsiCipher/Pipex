/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 02:02:07 by cipher            #+#    #+#             */
/*   Updated: 2022/06/03 02:22:26 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd1_handler(int *pipe_ends, char *infile_name, char *cmd, char **envp)
{
	int		infile_fd;

	infile_fd = open(infile_name, O_RDONLY);
	if (infile_fd == -1)
		print_sys_error(infile_name);
	close(pipe_ends[READ_END]);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_ends[WRITE_END], STDOUT_FILENO);
	close(pipe_ends[WRITE_END]);
	execute_cmd(cmd, envp);
}

void	cmd2_handler(int *pipe_ends, char *outfile_name, char *cmd, char **envp)
{
	int		outfile_fd;

	outfile_fd = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 00666);
	if (outfile_fd == -1)
		print_sys_error(outfile_name);
	close(pipe_ends[WRITE_END]);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(pipe_ends[READ_END], STDIN_FILENO);
	close(pipe_ends[READ_END]);
	execute_cmd(cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_ends[2];
	pid_t	cmd1_proc_pid;
	pid_t	cmd2_proc_pid;

	if (argc != 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 outfile", NULL);
	pipe(pipe_ends);
	cmd1_proc_pid = fork();
	if (cmd1_proc_pid == -1)
		print_error("Error: Failed to create a child process for CMD_1", NULL);
	else if (cmd1_proc_pid == 0)
		cmd1_handler(pipe_ends, argv[1], argv[2], envp);
	cmd2_proc_pid = fork();
	if (cmd2_proc_pid == -1)
		print_error("Error: Failed to create a child process for CMD_2", NULL);
	else if (cmd2_proc_pid == 0)
		cmd2_handler(pipe_ends, argv[4], argv[3], envp);
	close(pipe_ends[READ_END]);
	close(pipe_ends[WRITE_END]);
	waitpid(cmd1_proc_pid, NULL, 0);
	waitpid(cmd2_proc_pid, NULL, 0);
	return (0);
}
