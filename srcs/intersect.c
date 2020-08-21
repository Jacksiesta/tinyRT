#include "../includes/miniRT.h"

float	intersect_plan(t_vector origin, t_vector direction, t_plan *object)
{
	float	temp;
	float	A;
	float	B;
	float	touch;
	
	touch = 0;
	temp = dot_vector(*object->normal, *object->point);
	A = dot_vector(origin, *object->normal) - temp;
	B = dot_vector(direction, *object->normal);
	touch = -(A / B);
	if (touch < 0)
		return (0);
	return (touch);
}
