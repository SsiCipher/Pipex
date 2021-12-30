#include "pipex.h"

void	cmd1_handler(int *pipe_ends, char *infile_name, char *cmd, char **envp)
{
	int	infile_fd;

	infile_fd = open(infile_name, O_RDONLY);
	if (infile_fd == -1)
		print_error("Can't open infile\n");
	close(pipe_ends[0]);
	dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	execute_cmd(cmd, envp);
}

void	cmd2_handler(int *pipe_ends, char *outfile_name, char *cmd, char **envp)
{
	int		outfile_fd;

	outfile_fd = open(outfile_name, O_RDWR | O_CREAT, 00666);
	if (outfile_fd == -1)
		print_error("Can't open outfile\n");
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	execute_cmd(cmd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_ends[2];
	pid_t	cmd1_proc_pid;
	pid_t	cmd2_proc_pid;

	if (argc != 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	pipe(pipe_ends);
	cmd1_proc_pid = fork();
	if (cmd1_proc_pid == -1)
		print_error("The fork function for cmd1 failed\n");
	else if (cmd1_proc_pid == 0)
		cmd1_handler(pipe_ends, argv[1], argv[2], envp);
	cmd2_proc_pid = fork();
	if (cmd2_proc_pid == -1)
		print_error("The fork function for cmd2 failed\n");
	else if (cmd2_proc_pid == 0)
		cmd2_handler(pipe_ends, argv[4], argv[3], envp);
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	return (0);
}
