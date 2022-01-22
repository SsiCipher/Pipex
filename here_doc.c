/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 01:53:59 by cipher            #+#    #+#             */
/*   Updated: 2022/01/22 01:56:52 by cipher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include "libgnl/get_next_line.h"

//     0       1        2     3    4     5
// ./pipex here_doc LIMITER CMD1 CMD2 Outfile

void	start_here_doc(char *limiter)
{
	int		pipe_ends[2];
	pid_t	proc_pid;
	char	*line;

	pipe(pipe_ends);
	proc_pid = fork();
	if (proc_pid == -1)
		print_error("Error: Fork failed");
	else if (proc_pid == 0)
	{
		close(pipe_ends[READ_END]);
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(pipe_ends[WRITE_END], line, ft_strlen(line));
			line = get_next_line(STDIN_FILENO);
		}
	}
	else
	{
		waitpid(proc_pid, NULL, 0);
		close(pipe_ends[WRITE_END]);
		dup2(pipe_ends[READ_END], STDIN_FILENO);
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
		print_error("Error: Fork failed");
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
			print_error("Error: Coudn't create outfile");
		close(pipe_ends[WRITE_END]);
		dup2(pipe_ends[READ_END], STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		execute_cmd(cmd2, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 6)
		print_error("Usage: ./pipex here_doc LIMITER CMD1 CMD2 Outfile");
	else if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		start_here_doc(argv[2]);
		exec_here_doc(argv[3], argv[4], argv[5], envp);
	}

	return (0);
}
