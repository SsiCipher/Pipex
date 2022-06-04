/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.redo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:52:17 by yanab             #+#    #+#             */
/*   Updated: 2022/06/04 19:30:34 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_usage(int argc, char **argv)
{
	int		is_here_doc;
	char	*normal_error;
	char	*here_doc_error;

	normal_error = "Usage: ./pipex here_doc LIMITER cmd_1 cmd_2 outfile";
	here_doc_error = "Usage: ./pipex infile cmd_1 cmd_2 [...cmds] outfile";
	if (argc == 1)
		print_error("Usage: ./pipex infile cmd_1 cmd_2 [... other_cmds] outfile\n\
       ./pipex here_doc LIMITER cmd_1 cmd_2 outfile", NULL);
	is_here_doc = !ft_strcmp(argv[1], "here_doc");
	if (is_here_doc && argc != 6)
		print_error(normal_error, NULL);
	if (!is_here_doc && argc < 5)
		print_error(here_doc_error, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	pipe_ends[2];

	show_usage(argc, argv);
	pipe(pipe_ends);
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		start_here_doc(argv[2]);
		exec_here_doc(argv[3], argv[4], argv[5], envp);
	}
	else
	{
		i = -1;
		while (++i < argc - 3)
		{
			if (i < argc - 4)
				exec_cmd_in_proc(i, pipe_ends, argv, envp);
			else
				exec_last_cmd(argv[argc - 1], argv[i + 2], envp);
		}
		close(pipe_ends[READ_END]);
		close(pipe_ends[WRITE_END]);
	}
	return (0);
}
