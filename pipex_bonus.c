/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:52:17 by yanab             #+#    #+#             */
/*   Updated: 2022/01/07 03:34:18 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		pipe_ends[2];
	pid_t	cmd_proc_pid;
	int		infile_fd;
	int		outfile_fd;

	if (argc < 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile\n\
       ./pipex here_doc LIMITER cmd cmd1 outfile\n");
	pipe(pipe_ends);
	i = -1;
	while (++i < argc - 3)
	{
		cmd_proc_pid = fork();
		if (cmd_proc_pid == -1)
			print_error("Error: The fork function failed\n");
		else if (cmd_proc_pid == 0)
		{
			if (i == 0)
			{
				infile_fd = open(argv[1], O_RDONLY);
				if (infile_fd == -1)
					print_error("Error: Failed to open infile\n");
				close(pipe_ends[0]);
				dup2(infile_fd, STDIN_FILENO);
				dup2(pipe_ends[STDOUT_FILENO], STDOUT_FILENO);
				close(pipe_ends[STDOUT_FILENO]);
			}
			else if (i != argc - 4)
			{
				dup2(pipe_ends[0], STDIN_FILENO);
				close(pipe_ends[1]);
				close(pipe_ends[0]);
				// dup2(pipe_ends[1], STDOUT_FILENO);
			}
			else
			{
				outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 00666);
				if (outfile_fd == -1)
					print_error("Error: Failed to open outfile\n");
				close(pipe_ends[STDOUT_FILENO]);
				dup2(pipe_ends[STDIN_FILENO], STDIN_FILENO);
				// dup2(outfile_fd, STDOUT_FILENO);
				close(pipe_ends[STDIN_FILENO]);
			}
			execute_cmd(argv[i + 2], envp);
		}
	}
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	return (0);
}
