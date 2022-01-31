/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:52:17 by yanab             #+#    #+#             */
/*   Updated: 2022/01/31 13:51:29 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (argc != 6)
			print_error("Usage: /pipex here_doc LIMITER cmd cmd1 outfile\n");
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
