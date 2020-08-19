#ifndef SPHERE_H
# define SPHERE_H

#include <stdlib.h>
#include "vector.h"
/*
typedef struct 	s_pos
{
	double x;
	double y;
	double z;
}		t_pos;*/

typedef struct	s_sphere
{
	t_vector 	*center;
	float 		radius;
	int		color;
}		t_sphere;

t_sphere	*new_sphere(float radius, int color, t_vector *center);
t_sphere	*new_default_sphere(float radius, int color);

//t_sphere	*create_sphere(int radius, int color);
//t_pos		*create_pos(double x, double y, double z);

#endif
