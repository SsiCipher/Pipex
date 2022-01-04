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
			print_error("The fork function failed\n");
		else if (cmd_proc_pid == 0)
		{
			dprintf(STDERR_FILENO, "Process N^%d - PID: %d\n", i + 1, getpid());
			if (i != argc - 4)
			{
				if (i == 0)
				{
					infile_fd = open(argv[1], O_RDONLY);
					if (infile_fd == -1)
						print_error("Can't open infile\n");
					dup2(infile_fd, STDIN_FILENO);
				}
				else
					dup2(pipe_ends[STDIN_FILENO], STDIN_FILENO);
				dup2(pipe_ends[STDOUT_FILENO], STDOUT_FILENO);
				// exit(0);
			}
			else
			{
				close(pipe_ends[STDOUT_FILENO]);
				outfile_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 00666);
				if (outfile_fd == -1)
					print_error("Can't open outfile\n");
				dup2(pipe_ends[STDIN_FILENO], STDIN_FILENO);
				dup2(outfile_fd, STDOUT_FILENO);
				// exit(0);
			}
			execute_cmd(argv[i + 2], envp);
		}
		// else
			// waitpid(cmd_proc_pid, NULL, 0);
	}
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	return (0);
}
