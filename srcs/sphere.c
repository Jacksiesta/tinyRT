#include "../includes/sphere.h"

t_pos		*create_pos(double x, double y, double z)
{
	t_pos	*position;
	
	position = malloc(sizeof(t_pos));
	position->x = x;
	position->y = y;
	position->z = z;
	return (position);	
}

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

/*
t_sphere	*create_sphere(int radius, int color)
{
	t_sphere	*sphere;
	
	sphere = malloc(sizeof(t_sphere));
	sphere->radius = radius;
	sphere->color = color;
	sphere->center = create_pos(0, 0, 0);
	return (sphere);
}*/
