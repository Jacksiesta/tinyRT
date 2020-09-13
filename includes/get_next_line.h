#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int 	get_next_line(int fd, char **line);
void	ft_bzero(void *b, size_t len);
int	ft_strlen_endl(char const *s);
int	ft_strchr_pos(const char *s, int c);
char	*ft_strjoin_to_eol(char *s1, char *buf);

#endif
