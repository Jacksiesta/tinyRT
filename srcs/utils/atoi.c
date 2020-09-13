#include "../../includes/miniRT.h"
#include "../../includes/utils.h"

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

int	ft_atoc(char *line, int *color)
{
	int	x;
	int	y;
	int	n;
	int	rgb[3];	

	x = 0;
	n = 0;
	while (n <= 2)
	{
		if ((y = ft_atoi(&line[x], &rgb[n])) < 0)
			return (-1);
		if (rgb[n] < 0 || rgb[n] > 255)
			return (-1);
		x += y; //incr of len of first color
		if (n < 2 && line[x] != ',') // comma after colors, except for last one
			return (-1);
		else if (n < 2 && line[x] == ',')
			x++;
		n++;	
	}
	*color = rgb[0];
	*color = (*color << 8) + rgb[1];
	*color = (*color << 8) + rgb[2];
	return (x);
}

int	ft_atov(char *line, t_vector **v1)
{
	int	x;
	int	y;
	int	n;
	float	v[3];
	
	x = 0;
	n = 0;
	while (n <= 2)
	{
		if ((y = ft_atof(&line[x], &v[n])) < 0)
			return (-1);
		x += y;
		if (n < 2 && line[x] != ',')
			return (-1);
		else if (n < 2 && line[x] == ',')
			x++;
		n++;			
	}
	if (!(*v1 = new_vector(v[0], v[1], v[2])))
		return (-1);
	return (x);	
}

int	ft_atof(char *line, float *num)
{
	int	x;
	int	nb;
	double	sub_zero;

	if ((x = ft_atoi(line, &nb)) < 0)
		return (-1);
	*num = nb;
	if (line[x] == '.')
		x++;
	sub_zero = (num < 0) ? -0.1 : 0.1;
	while (line[x] && line[x] >= '0' && line[x] <= '9')
	{
		*num = *num + sub_zero * (line[x] - '0');
		sub_zero *= 0.1;	
	}
	return (x);
			
}
