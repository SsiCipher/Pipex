#include "pipex.h"

// PIPE[0] => Read
// PIPE[1] => Write

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		pipe_ends[2];
	pid_t	cmd_proc_pid;
	// int		infile_fd;
	// int		outfile_fd;

	(void)argv;
	(void)envp;

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
			close(pipe_ends[0]);
			dprintf(pipe_ends[1], "Inside process Number [%d] PID [%d]\n", i, getpid());
			dprintf(1, "Inside process Number [%d] PID [%d]\n", i, getpid());
			close(pipe_ends[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipe_ends[1]);
			printf("Parent process PID [%d]\n", getpid());
			char buff[1024];
			int rd = read(pipe_ends[0], buff, 1024);
			buff[rd] = '\0';
			printf("Pipe contains: %s", buff);
			close(pipe_ends[0]);
			wait(NULL);
		}
	}

	// close(pipe_ends[STDIN_FILENO]);
	// close(pipe_ends[STDOUT_FILENO]);
	return (0);
}
