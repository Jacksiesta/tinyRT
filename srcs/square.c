#include "../includes/miniRT.h"

t_square	*new_square(t_vector *center, t_vector *orientation, float size, int color)
{
	t_square 	*sq;
	t_vector	*angle;
	t_vector	*v[4];
	
	sq = malloc(sizeof(t_square));
	sq->center = center;
	sq->orientation = orientation;
	sq->size = size;
	sq->color = color;
	angle = new_vector(orientation->x * 180, orientation->y * 180, orientation->z * 180);
	v[0] = new_vector(sq->size / 2, sq->size / 2, 0);
	v[1] = new_vector( -(sq->size / 2), sq->size / 2, 0);
	v[2] = new_vector(sq->size / 2, -(sq->size / 2), 0);
	v[3] = new_vector( -(sq->size / 2), -(sq->size / 2), 0);
	rot(v[0], angle);
	rot(v[1], angle);
	rot(v[2], angle);
	rot(v[3], angle);
	sq->a = add_vector(*v[0], *sq->center);
	sq->b = add_vector(*v[1], *sq->center);
	sq->c = add_vector(*v[2], *sq->center);
	sq->d = add_vector(*v[3], *sq->center);
	sq->reflection = -1;
	return (sq);
}
