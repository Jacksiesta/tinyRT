#include "../includes/miniRT.h"

t_plan	*new_plan(t_vector *p, t_vector *norm, int c)
{
	t_plan	*plan;
	
	plan = malloc(sizeof(t_plan));
	plan->point = p;
	plan->normal = norm;
	plan->shiny = -1;
	plan->reflective = -1;
	plan->color = c;
	return (plan);
}
