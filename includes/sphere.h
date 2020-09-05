#ifndef SPHERE_H
# define SPHERE_H

#include <stdlib.h>
#include "vector.h"

typedef struct	s_sphere
{
	t_vector 	*center;
	float 		radius;
	int		color;
	float		shiny;
	float		reflection;
}		t_sphere;

t_sphere	*new_sphere(float radius, int color, float reflection, t_vector *center);
t_sphere	*new_default_sphere(float radius, int color);
void		set_reflection(t_sphere *sphere, float reflection);

#endif
