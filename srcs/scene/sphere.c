#include "../../includes/sphere.h"

t_sphere	*new_sphere(float radius, int color, float reflection, t_vector *center)
{
	t_sphere	*sphere;
	
	sphere = malloc(sizeof(t_sphere));
	sphere->radius = radius;
	sphere->color = color;
	sphere->center = center;
	sphere->reflection = reflection;
	return (sphere);	
}

t_sphere	*new_default_sphere(float radius, int color)
{
	return (new_sphere(radius, color, -1, new_vector(0, 0, 0)));	
}

void		set_reflection(t_sphere *sphere, float reflection)
{
	sphere->reflection = reflection;
}

