#ifndef SQUARE_H
# define SQUARE_H

typedef struct	s_square
{
	t_vector	*center;
	t_vector	*orientation;
	t_vector	*a;
	t_vector	*b;
	t_vector	*c;
	t_vector	*d;
	float		size;
	int		color;
	float		shiny;
	float		reflective;	
}		t_square;

#endif
