/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cipher <cipher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 17:52:08 by yanab             #+#    #+#             */
/*   Updated: 2022/01/22 02:07:23 by cipher           ###   ########.fr       */
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
# include <string.h>
# include "../libft/libft.h"
# include "../libgnl/get_next_line.h"

#define READ_END 0
#define WRITE_END 1

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
}	s_mp_args;

// utils.c
void	print_error(char *str);
char	**get_env_paths(char **envp);
char	*get_cmd_path(char *cmd_name, char **envp);
void	execute_cmd(char *cmd, char **envp);

// utils_bonus.c
void	start_here_doc(char *limiter);
void	exec_here_doc(char *cmd1, char *cmd2, char *outfile_name, char **envp);

#endif
