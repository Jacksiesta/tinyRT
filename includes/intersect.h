#ifndef INTERSECT_H
# define INTERSECT_H

#include "plan.h"
#include "square.h"
#include "triangle.h"

float	intersect_plan(t_vector origin, t_vector direction, t_plan *object);
float	intersect_square(t_vector origin, t_vector direction, t_square *sq);
float	intersect_triangle(t_vector origin, t_vector direction, t_triangle *tr);
float	intersect_cyl(t_vector origin, t_vector direction, t_cylinder *cy);


#endif
