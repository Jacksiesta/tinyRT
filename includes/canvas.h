#ifndef CANVAS_H
# define CANVAS_H

#include <stdlib.h>

typedef struct	s_canvas
{
	float	width;
	float	height;
	float	distance;	
}		t_canvas;

t_canvas	*new_canvas(int width, int height, int distance);
//t_canvas	*create_canvas(int w, int h, int d);

#endif
