#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include "./libft/libft.h"

// utils.c
void	print_error(char *str);
char	**get_env_paths(char **envp);
char	*get_cmd_path(char *cmd_name, char **envp);
void	execute_cmd(char *cmd, char **envp);

#endif
