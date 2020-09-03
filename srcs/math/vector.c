#include "../../includes/vector.h"

void		set_vector(t_vector *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

t_vector	*new_vector(float x, float y, float z)
{
	t_vector	*vector;
	
	vector = malloc(sizeof(t_vector));
	set_vector(vector, x, y, z);
	return (vector);
}
