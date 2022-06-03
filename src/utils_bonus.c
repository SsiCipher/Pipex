/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 02:01:26 by cipher            #+#    #+#             */
/*   Updated: 2022/06/03 03:44:38 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start_here_doc(char *limiter)
{
	int		pipe_ends[2];
	pid_t	proc_pid;
	char	*line;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	pipe(pipe_ends);
	proc_pid = fork();
	if (proc_pid == -1)
		print_error("Error: Fork failed", NULL);
	else if (proc_pid == 0)
	{
		close(pipe_ends[READ_END]);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(EXIT_SUCCESS);
		printf("%s\n", line);
		while (line)
		{
			if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
				exit(EXIT_SUCCESS);
			write(pipe_ends[WRITE_END], line, ft_strlen(line));
			line = get_next_line(STDIN_FILENO);
		}
	}
	else
	{
		close(pipe_ends[WRITE_END]);
		dup2(pipe_ends[READ_END], STDIN_FILENO);
		waitpid(proc_pid, NULL, 0);
	}
}

void	exec_here_doc(char *cmd1, char *cmd2, char *outfile_name, char **envp)
{
	int		outfile_fd;
	int		pipe_ends[2];
	pid_t	proc_pid;

	pipe(pipe_ends);
	proc_pid = fork();
	if (proc_pid == -1)
		print_error("Error: Fork failed", NULL);
	else if (proc_pid == 0)
	{
		close(pipe_ends[READ_END]);
		dup2(pipe_ends[WRITE_END], STDOUT_FILENO);
		execute_cmd(cmd1, envp);
	}
	else
	{
		outfile_fd = open(outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (outfile_fd == -1)
			print_error("Error: Coudn't create outfile", NULL);
		close(pipe_ends[WRITE_END]);
		dup2(pipe_ends[READ_END], STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		execute_cmd(cmd2, envp);
	}
}

void	execute_start_cmds(int cmd_i, int *pipe_ends, char **argv, char **envp)
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

void	run_cmd_in_proc(int cmd_i, int *pipe_ends, char **argv, char **envp)
{
	pid_t	cmd_proc_pid;

	cmd_proc_pid = fork();
	if (cmd_proc_pid == -1)
		print_error("Error: The fork function failed\n", NULL);
	else if (cmd_proc_pid == 0)
		execute_start_cmds(cmd_i, pipe_ends, argv, envp);
	else
	{
		close(pipe_ends[WRITE_END]);
		dup2(pipe_ends[READ_END], STDIN_FILENO);
		close(pipe_ends[READ_END]);
		pipe(pipe_ends);
	}
}

void	execute_last_cmd(char *outfile_name, char *cmd, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(outfile_name, O_RDWR | O_CREAT | O_TRUNC, 00666);
	if (outfile_fd == -1)
		print_error("Error: Failed to open outfile\n", NULL);
	dup2(outfile_fd, 1);
	close(outfile_fd);
	execute_cmd(cmd, envp);
}
