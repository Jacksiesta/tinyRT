#include "../../includes/miniRT.h"

t_vector	*color_to_rgb(unsigned int color)
{
	int red;
	int green;
	int blue;
	
	blue = (int)(color % 256);
	green = (int)(((color - blue) / 256) % 256);
	red = (int)(((color - blue) / (256 * 256)) - green / 256);
	return (new_vector((float)red, (float)green, (float)blue));		
}

int		rgb_to_color(t_vector *rgb)
{
	int color;
	
	color = (int)(((int)rgb->x));
	color = (int)((color << 8) + (int)rgb->y);
	color = (int)((color << 8) + (int)rgb->z);
	return (color);	
}

void		rearrange_rgb(t_vector *color)
{
	color->x = (color->x > 255) ? 255 : color->x;
	color->x = (color->x < 0) ? 0 : color->x;
	color->y = (color->y > 255) ? 255 : color->y;
	color->y = (color->y < 0) ? 0 : color->y;
	color->z = (color->z > 255) ? 255 : color->z;
	color->z = (color->z < 0) ? 0 : color->z;	
}
