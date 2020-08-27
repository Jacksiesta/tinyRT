#ifndef TRIANGLE_H
# define TRIANGLE_H

typedef struct	s_triangle
{
	t_vector	*a;
	t_vector	*b;
	t_vector	*c;
	int		color;
	float		reflection;
}		t_triangle;

t_triangle	*new_triangle(t_vector *a, t_vector *b, t_vector *c, int color);

#endif
