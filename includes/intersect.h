#ifndef INTERSECT_H
# define INTERSECT_H

#include "plan.h"
#include "square.h"

float	intersect_plan(t_vector origin, t_vector direction, t_plan *object);
float	intersect_square(t_vector origin, t_vector direction, t_square *sq);
/*
float	interesect_triqngle(t_vector origin, t_vector direction, t_triangle *tr);*/


#endif
