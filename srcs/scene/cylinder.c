#include "../../includes/miniRT.h"

t_cylinder	*new_cylinder(t_vector *center, t_vector *orientation, float diameter, float h, int color)
{
	t_cylinder	*cylinder;
	t_vector	*var;
	float		denom;

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->center = center;
	cylinder->orientation = orientation;
	//fabs(x) for absolute |x|
	denom = fabs(orientation->x) + fabs(orientation->y) + fabs(orientation->z);
	// check caps
	var = new_vector(h / 2 * orientation->x / denom, h / 2 * orientation->y / denom, h / 2 * orientation->z / denom);
	cylinder->point1 = add_vector(*cylinder->center, *var);
	free(var);
	var = new_vector(-h / 2 * orientation->x / denom, -h / 2 * orientation->y / denom, -h / 2 * orientation->z / denom);
	cylinder->point2 = add_vector(*cylinder->center, *var);
	free(var);
	cylinder->diameter = diameter;
	cylinder->height = h;
	cylinder->color = color; 
	cylinder->reflection = -1;
	return (cylinder);	
}

