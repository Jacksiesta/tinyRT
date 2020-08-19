#include "../includes/sphere.h"

t_sphere	*new_sphere(float radius, int color, t_vector *center)
{
	t_sphere	*sphere;
	
	sphere = malloc(sizeof(t_sphere));
	sphere->radius = radius;
	sphere->color = color;
	sphere->center = center;
	return (sphere);	
}

t_sphere	*new_default_sphere(float radius, int color)
{
	return (new_sphere(radius, color, new_vector(0, 0, 0)));	
}

