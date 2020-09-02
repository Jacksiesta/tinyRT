#include "../../includes/miniRT.h"

int	parsing_sphere(t_scene **scene, char *line)
{
	t_vector	*center;
	float		radius;
	int		color;
	int		x[3];
	
	x[0] = 2;
	x[1] = -1;
	x[2] = 0;
	while (++x[1] < 4 && (x[0] += x[2]) && (line[x[0]] == ' ' || line[x[0]] == '\t'))		
	
}

int		parsing_sphere(s_scene **scene, char *l)
{
	int			i[3];
	s_vector	*center;
	float		radius;
	int			color;

	i[0] = 2;
	i[2] = 0;
	i[1] = -1;
	while (++i[1] < 4 && (i[0] += i[2]) && (l[i[0]] == ' ' || l[i[0]] == '\t'))
	{
		while (l[i[0]] == ' ' || l[i[0]] == '\t')
			i[0]++;
		if (!i[1] && (((l[i[0]] < '0' || l[i[0]] > '9') && l[i[0]] != '-')
		|| (i[2] = ft_atov(&l[i[0]], &center)) < 0))
			return (-1);
		if ((i[1] == 1) && ((l[i[0]] < '0' || l[i[0]] > '9') ||
		(i[2] = ft_atof(&l[i[0]], &radius)) < 0))
			return (free_and_return_minus_one(center));
		if ((i[1] == 2) && ((l[i[0]] < '0' || l[i[0]] > '9') ||
		(i[2] = ft_atoc(&l[i[0]], &color)) < 0))
			return (free_and_return_minus_one(center));
	}
	if (l[i[0]] && l[i[0]] != ' ' && l[i[0]] != '\t')
		return (free_and_return_minus_one(center));
	return (!l[i[0]] && (!(add_back(&(*scene)->objects, TYPE_SPHERE, new_sphere(
radius, color, 10, center))) ? 0 : free_and_return_minus_one(center)));
	return (0);
}
