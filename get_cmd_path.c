#include "pipex.h"

char	*get_cmd_path(char *cmd_name, char **envp)
{
	// Find line that contains "PATH:" in envp
	// Split that line with ':' starting from i=5
	// Try every for every path:
		// join path with '/'
		// join path with cmd
		// use access function with the new_path
	// return the right path to cmd
	char **cmd_name_split = ft_split(cmd_name, ' ');

}

int main(int argc, char **argv, char **envp)
{
	char *cmd_path = get_cmd_path("ls -la", envp);
	printf("The path for 'ls' command is: [%s]\n", cmd_path);

	return (0);
}
