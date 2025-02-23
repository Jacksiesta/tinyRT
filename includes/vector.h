#ifndef VECTOR_H
# define VECTOR_H

#include <stdlib.h>

typedef struct	s_vector
{
	float x;
	float y;
	float z;
}				t_vector;

typedef struct	s_light_vector
{
	t_vector	*point;
	t_vector	*normal;
	t_vector	*view;
	float		reflection;
	float		shiny;
}		t_light_vector;

typedef struct	s_rotation
{
	t_vector	*x;
	t_vector	*y;
	t_vector	*z;	
}		t_rotation;

/* VECTOR_MATH */

float		dot_vector(t_vector v1, t_vector v2);
float		len_vector(t_vector v);
float		distance_points(t_vector a, t_vector b);
t_vector	*sub_vector(t_vector v1, t_vector v2);
t_vector	*add_vector(t_vector v1, t_vector v2);
t_vector	*scale_vector(float c, t_vector v);
t_vector	*cross_product(t_vector v1, t_vector v2);

/* VECTOR */

void		set_vector(t_vector *vector, float x, float y, float z);
t_vector	*new_vector(float x, float y, float z);

/* VECTOR_COLOR */

t_vector	*color_to_rgb(unsigned int color);
int		rgb_to_color(t_vector *rgb);
void		rearrange_rgb(t_vector *vector);

/* ROTATION */
t_rotation	*new_rotation(t_vector *rota_x, t_vector *rota_y, t_vector *rota_z);
void		rx(t_vector *v, float x);
void		ry(t_vector *v, float y);
void		rz(t_vector *v, float z);
void		rot(t_vector *v, t_vector *angle);
void		anti_rot(t_vector *v, t_vector *angle);

#endif
