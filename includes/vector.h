#ifndef VECTOR_H
# define VECTOR_H

#include <stdlib.h>

typedef struct	s_vector
{
	float x;
	float y;
	float z;	
}		t_vector;

/* VECTOR_MATH */

float		dot_vector(t_vector v1, t_vector v2);
float		len_vector(t_vector v);
t_vector	*sub_vector(t_vector v1, t_vector v2);
t_vector	*add_vector(t_vector v1, t_vector v2);
t_vector	*scale_vector(float c, t_vector v);

/* VECTOR */

void		set_vector(t_vector *vector, float x, float y, float z);
t_vector	*new_vector(float x, float y, float z);

/* VECTOR_COLOR */

t_vector	*color_to_rgb(unsigned int color);
int		rgb_to_color(t_vector *rgb);
void		rearrange_rgb(t_vector *vector);

#endif
