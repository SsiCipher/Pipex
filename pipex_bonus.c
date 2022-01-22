/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:52:17 by yanab             #+#    #+#             */
/*   Updated: 2022/01/22 02:05:08 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_start_cmds(int cmd_i, int *pipe_ends, char **argv, char **envp)
{
	int	infile_fd;

	if (cmd_i == 0)
	{
		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd == -1)
			print_error("Error: Failed to open infile\n");
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
	}
	close(pipe_ends[READ_END]);
	dup2(pipe_ends[WRITE_END], STDOUT_FILENO);
	close(pipe_ends[WRITE_END]);
	execute_cmd(argv[cmd_i + 2], envp);
}

void	execute_last_cmd(char *outfile_name, char *cmd, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC, 00666);
	if (outfile_fd == -1)
		print_error("Error: Failed to open outfile\n");
	dup2(outfile_fd, 1);
	close(outfile_fd);
	execute_cmd(cmd, envp);
}

void	handle_exit(pid_t proc_pid)
{
	int	proc_status;

	(void)proc_pid;
	waitpid(proc_pid, &proc_status, 0);
	if (proc_status != 0)
		exit(EXIT_FAILURE);
}

void	run_cmd_in_proc(int cmd_i, int *pipe_ends, char **argv, char **envp)
{
	pid_t	cmd_proc_pid;

	cmd_proc_pid = fork();
	if (cmd_proc_pid == -1)
		print_error("Error: The fork function failed\n");
	else if (cmd_proc_pid == 0)
		execute_start_cmds(cmd_i, pipe_ends, argv, envp);
	else
	{
		// handle_exit(cmd_proc_pid);
		close(pipe_ends[WRITE_END]);
		dup2(pipe_ends[READ_END], STDIN_FILENO);
		close(pipe_ends[READ_END]);
		pipe(pipe_ends);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int			i;
	int			pipe_ends[2];

	if (argc < 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile\n\
       ./pipex here_doc LIMITER cmd cmd1 outfile\n");
	pipe(pipe_ends);
	if (strcmp(argv[1], "here_doc") == 0)
	{
		start_here_doc(argv[2]);
		exec_here_doc(argv[3], argv[4], argv[5], envp);
	}
	else
	{
		i = -1;
		while (++i < argc - 3)
		{
			if (i != argc - 4)
				run_cmd_in_proc(i, pipe_ends, argv, envp);
			else
				execute_last_cmd(argv[argc - 1], argv[i + 2], envp);
		}
		close(pipe_ends[READ_END]);
		close(pipe_ends[WRITE_END]);
	}
	return (0);
}
