#include "pipex.h"

void	print_error(char *str)
{
	while (*str)
		write(1, str++, 1);
	exit(1);
}

void	execude_cmd(char *cmd, char **envp)
{

}

void	cmd1_handler(int *pipe_ends, char *infile_name, char cmd, char **envp)
{
	int	infile_fd;

	infile_fd = open(infile_name, O_RDONLY);
	if (infile_fd == -1)
		print_error("Can't open infile\n");

	dup2(infile_fd, STDIN_FILENO);
	dup2(pipe_ends[1], STDOUT_FILENO);
	close(pipe_ends[0]);
	execute_cmd(cmd, envp);
}

void	cmd2_handler(int *pipe_ends, char *outfile_name, char cmd, char **envp)
{
	int		outfile_fd;
	outfile_fd = open(argv[4], O_RDWR | O_CREAT);
	if (outfile_fd == -1)
		print_error("Can't open outfile\n");

	dup2(pipe_ends[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(pipe_ends[1]);
	execute_cmd(cmd, envp);
}

int main(int argc, char **argv, char **envp)
{
	int		pipe_ends[2];
	pid_t	cmd1_proc_pid;
	pid_t	cmd2_proc_pid;

	// Check if the right count of args is given
	if (argc != 5)
		print_error("Usage: ./pipex infile cmd1 cmd2 outfile\n");

	// Open a pipe to use with the 2 processes
	pipe(pipe_ends);

	// Create a child process for cmd1 + check for errors
	cmd1_proc_pid = fork();
	if (cmd1_proc_pid == -1)
		print_error("The fork function for cmd1 failed\n");
	else if (cmd1_proc_pid == 0)
		cmd1_handler(pipe_ends, argv[1], argv[2], envp);
	else
		waitpid(cmd1_proc_pid, NULL, 0);

	// Create a child process for cmd2 + check for errors
	cmd2_proc_pid = fork();
	if (cmd2_proc_pid == -1)
		print_error("The fork function for cmd2 failed\n");
	else if (cmd2_proc_pid == 0)
		cmd2_handler(pipe_ends, argv[4], argv[3], envp);
	else
		waitpid(cmd2_proc_pid, NULL, 0);

	// Close both pipe ends
	close(pipe_ends[0]);
	close(pipe_ends[1]);

	return (0);
}
