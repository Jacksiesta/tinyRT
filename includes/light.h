#ifndef LIGHT_H
# define LIGHT_H

#include <stdlib.h>
#include "vector.h"

# define TYPE_AMBIENT 0
# define TYPE_POINT 1
# define TYPE_DIRECTIONAL 2

typedef struct 	s_light
{
	int		type;
	float		intensity;
	t_vector	*vector;	
}		t_light;

t_light		*new_default_light(int type, float intensity);

#endif
