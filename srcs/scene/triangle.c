#include "../../includes/miniRT.h"

t_triangle	*new_triangle(t_vector *a, t_vector *b, t_vector *c, int color)
{
	t_triangle	*triangle;
	
	triangle = malloc(sizeof(t_triangle));
	triangle->a = a;
	triangle->b = b;
	triangle->c = c;
	triangle->color = color;
	triangle->reflection = -1;
	return (triangle);	
}
