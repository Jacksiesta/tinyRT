#ifndef PLAN_H
# define PLAN_H

typedef struct	s_plan
{
	t_vector	*point;
	t_vector	*normal;
	float		shiny;
	float		reflection;
	int		color;	
}		t_plan;

t_plan	*new_plan(t_vector *p, t_vector *v, int c);

#endif
