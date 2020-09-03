#include "../../includes/canvas.h"
#include "../../includes/miniRT.h"
#include "../../includes/vector.h"

t_canvas	*new_canvas(int width, int height, int distance)
{
	t_canvas	*canvas;
	
	canvas = malloc(sizeof(t_canvas));
	canvas->width = width;
	canvas->height = height;
	canvas->distance = distance;
	return (canvas);	
}
