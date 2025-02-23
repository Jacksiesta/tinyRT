#ifndef CYLINDER_H
# define CYLINDER_H

typedef struct	s_cylinder
{
	t_vector	*center;
	t_vector	*orientation;
	t_vector	*point1;
	t_vector	*point2;
	float		diameter;
	float		height;
	int		color;
	float		reflection;
	float		shiny;
}		t_cylinder;

t_cylinder	*new_cylinder(t_vector *center, t_vector *orientation, float diameter, float h, int color);

#endif
