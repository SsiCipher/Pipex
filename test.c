/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:52:17 by yanab             #+#    #+#             */
/*   Updated: 2022/01/07 03:37:02 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// < infile grep are | wc -l | xargs > outfile
// ./a.out infile "grep are" "wc -l" "xargs" outfile

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
			dup2(pipe_ends[1], 1);
			close(pipe_ends[0]);
			close(pipe_ends[1]);
			execute_cmd(argv[i + 2], envp);
		}
		else
		{
			dup2(pipe_ends[0], 0);
			close(pipe_ends[1]);
			close(pipe_ends[0]);
			if (i != argc - 4)
				pipe(pipe_ends);
		}
	}
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	return (0);
}
