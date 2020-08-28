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
}		t_cylinder;

#endif
