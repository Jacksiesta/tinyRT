#ifndef CANVAS_H
# define CANVAS_H

#include <stdlib.h>

typedef struct	s_canvas
{
	double	width;
	double	height;
	double	distance;	
}		t_canvas;

t_canvas	*create_canvas(int w, int h, int d);

#endif
