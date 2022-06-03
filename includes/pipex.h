/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:52:08 by yanab             #+#    #+#             */
/*   Updated: 2022/06/03 02:06:16 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"
# include "../libgnl/get_next_line.h"

# define READ_END 0
# define WRITE_END 1

typedef struct s_hd_args
{
	char	*limiter;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
}	t_hd_args;

typedef struct s_mp_args
{
	int		cmds_count;
	int		pipe_ends[2];
	char	**cmds;
	char	**envp;
	char	*infile_name;
	char	*outfile_name;
}	t_mp_args;

// utils.c
void	print_error(char *error_msg, char *arg);
void	print_sys_error(char *arg);
char	**get_env_paths(char **envp);
char	*get_cmd_path(char *cmd_name, char **envp);
void	execute_cmd(char *cmd, char **envp);

// utils_bonus.c
void	start_here_doc(char *limiter);
void	exec_here_doc(char *cmd1, char *cmd2, char *outfile_name, char **envp);
void	execute_start_cmds(int cmd_i, int *pipe_ends, char **argv, char **envp);
void	run_cmd_in_proc(int cmd_i, int *pipe_ends, char **argv, char **envp);
void	execute_last_cmd(char *outfile_name, char *cmd, char **envp);

#endif
