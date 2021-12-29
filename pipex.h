#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
// # include <sys/wait.h>
# include <string.h>

char	**ft_split(char *str, char sep);
char	*strstr(char *haystack, char *needle);

#endif
