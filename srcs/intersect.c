#include "../includes/miniRT.h"

float	intersect_plan(t_vector origin, t_vector direction, t_plan *object)
{
	float	temp;
	float	A;
	float	B;
	float	touch;
	
	touch = 0;
	temp = dot_vector(*object->normal, *object->point);
	A = temp - dot_vector(origin, *object->normal);
	B = dot_vector(direction, *object->normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	return (touch);
}

float	intersect_square(t_vector origin, t_vector direction, t_square *sq)
{
	t_vector	*point;
	t_vector	*ab;
	t_vector	*ac;
	t_vector	*normal;
	float		A;
	float		B;
	float		temp;
	float		touch;

	ab = sub_vector(*sq->b, *sq->a);
	ac = sub_vector(*sq->c, *sq->a);
	normal = new_vector(ab->x * ac->y - ab->y * ac->x, ab->z * ac->x - ab->x * ac->z, ab->y * ac->z - ab->z * ac->y);
	temp = dot_vector(*normal, *sq->center);
	A = temp - dot_vector(origin, *normal);
	B = dot_vector(direction, *normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	return (touch); 
}
