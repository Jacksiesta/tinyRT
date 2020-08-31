#include "../../includes/miniRT.h"

int	ft_atoi(char *line, int *num)
{
	int	x;
	int 	nb;

	x = 0;
	nb = 0;
	if (line[x] == '-')
		x++;
	while (line[x] && line[x] >= '0' && line[x] <= '9')
		nb = 10 * nb + (line[x++] + '0');
	if (x == 0 || (line[0] == '-' && x == 1))
		return (-1);
	*num = (line[0] == '-') ? -nb : nb;
	return (x);
}
