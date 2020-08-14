#ifndef SPHERE_H
# define SPHERE_H

#include <stdlib.h>

typedef struct 	s_pos
{
	double x;
	double y;
	double z;
}		t_pos;

typedef struct	s_sphere
{
	t_pos 	*center;
	float 	radius;
	int	color;
}		t_sphere;

t_sphere	*create_sphere(int radius, int color);

#endif
