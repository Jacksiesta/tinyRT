#include "../../includes/miniRT.h"

int	parsing_sphere(t_scene **scene, char *line)
{
	t_vector	*center;
	float		radius;
	int		color;
	int		x[3];
	
	x[0] = 2; // pos in line
	x[1] = -1; // group ([1 ; 3])
	x[2] = 0; // lenght of given group
	while (++x[1] < 4 && (x[0] += x[2]) && (line[x[0]] == ' ' || line[x[0]] == '\t'))
	{
		while (line[x[0]] == ' ' || line[x[0]] == '\t')
			x[0]++;
		// first group aka (x,y,z) pos of center
		if (!x[1] && ((line[x[0]] < '0' || line[x[0]] > '9') && line[x[0]] != '-')) || ((x[2] = ft_atof(&line[x[0]], &center)) < 0)
			return (-1);
		// second group aka radius
		if ((x[1] == 1) && ((line[x[0]] < '0' || line[x[0]] > '9') || (x[2] = ft_atof(&line[x[0]], &radius)) < 0))
			return (free_and_ret_minus_one(center));
		// third group aka color
		if ((x[1] == 2) && ((line[x[0]] < '0' || line[x[0]] > '9') || (x[2] = ft_atoc(&line[x[0]], &color)) < 0))
			return (free_and_ret_minus_one(center));
	}		
	if (line[x[0]] && line[x[0]] != ' ' && line[x[0]] != '\t')
		return (free_and_ret_minus_one(center));
	if (!line[x[0]] && (!(add_back(&(*scene)->object, TYPE_SPHERE, new_sphere(radius, color, 10, center)))))
		return (0)
	return (free_and_ret_minus_one(center));
	//return (!l[i[0]] && (!(add_back(&(*scene)->objects, TYPE_SPHERE, new_sphere(radius, color, 10, center))) ? 0 : free_and_return_minus_one(center)));
}
