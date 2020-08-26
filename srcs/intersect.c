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
	printf("touch is %f\n", touch);
	return (touch);
}

float	intersect_square(t_vector origin, t_vector direction, t_square *sq)
{
	t_vector	*point;
	t_vector	*ab;
	t_vector	*ac;
	t_vector	*ap;
	t_vector	*normal;
	t_vector	*var;
	float		A;
	float		B;
	float		X;
	float		Y;
	float		temp;
	float		touch;

	ab = sub_vector(*sq->b, *sq->a);
	ac = sub_vector(*sq->c, *sq->a);
	// cross prod of (ab x ac) to get normal 
	normal = new_vector(ab->x * ac->y - ab->y * ac->x, ab->z * ac->x - ab->x * ac->z, ab->y * ac->z - ab->z * ac->y);
	temp = dot_vector(*normal, *sq->center);
	A = temp - dot_vector(origin, *normal);
	B = dot_vector(direction, *normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	var = scale_vector(touch, direction);
	point = add_vector(origin, *var);
	free(var);
	ap = sub_vector(*point, *sq->a);
	X = dot_vector(*ap, *ac) / dot_vector(*ac, *ac);
	Y = dot_vector(*ap, *ab) / dot_vector(*ab, *ab);
	if (X >= 0 && X <= 1 && Y >= 0 && Y <= 1)
		return (touch);
	return (0); 
}
/*
float	intersect_triangle(t_vector origin, t_vector direction, t_triangle *tr)
{
	t_vector	*ab;
	t_vector	*ac;
	
	ab = sub_vector(*tr->b, *tr->a);
	ac = sub_vector(*tr->c, *tr->a);
	//cross prod 	
}*/
