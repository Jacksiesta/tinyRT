#include "../../includes/get_next_line.h"
//#include "../../includes/miniRT.h"

void	ft_bzero(void *b, size_t len)
{
	while (len > 0)
	{
		*(char *)b++ = 0;
		len--;	
	}
}

int	ft_strlen_endl(char const *s) //len till end of line
{
	int x;

	x = 0;
	while (s && s[x] && s[x] != '\n')
		x++;
	return (x);
}

int	ft_strchr_pos(const char *s, int c) //search for c in s, returns pos if E
{
	int pos;
	
	pos = 0;
	while (s && s[pos])
	{
		if (s[pos] == c)
			return (pos);
		pos++;	
	}
	if (s && s[pos] == c)
		return (pos);
	return (-1);
}

// join s1 and buf up until eol
char	*ft_strjoin_to_eol(char *s1, char *buf)
{
	char 	*tab;
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	if (!(tab = malloc(ft_strlen_endl(s1) + ft_strlen_endl(buf) + 1)))
		return (NULL);
	while (s1 && s1[y])
		tab[x++] = s1[y++];
	while (buf && *buf && *buf != '\n')
		tab[x++] = *buf++;
	tab[x] = 0;
	free(s1);
	return (tab);
}

int	get_next_line(int fd, char **line)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	int		ret;
	int		x;
	
	if (BUFFER_SIZE < 1 || fd < 0 || fd > FOPEN_MAX || !line
			|| !(*line = ft_strjoin_to_eol(NULL, buf[fd])))
		return (-1);
	ret = 1;
	while (ft_strchr_pos(buf[fd], '\n') == -1 && ret && ret != -1)
	{
		ft_bzero(buf[fd], BUFFER_SIZE + 1);
		ret = read(fd, buf[fd], BUFFER_SIZE);
		if (!(*line = ft_strjoin_to_eol(*line, buf[fd])))
			return (-1);
	}
	x = 0;
	ret = ft_strchr_pos(buf[fd], '\n') + 1;
	if (buf[fd][0] == 0)
		return (0);
	while (buf[fd][ret] != '\0' && ret)
		buf[fd][x] = buf[fd][ret++];
	buf[fd][x] = 0;
	return (1);
}
