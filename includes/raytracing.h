#ifndef RAYTRACING_H
# define RAYTRACING_H

#include "scene.h"

float	compute_lighting(t_light_vector *l_vector, t_lstobject *lights);
int	calculate_new_color(t_lstobject *object, t_lstobject *lights, t_light_vector *l_vector);
int	trace_ray(t_vector direction, t_scene *scene);

#endif
