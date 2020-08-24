#ifndef RAYTRACING_H
# define RAYTRACING_H

#include "scene.h"

float	compute_lighting(t_light_vector *l_vector, t_lstobject *lights);
float	intersect_sphere(t_vector obs, t_vector direction, t_sphere *object);
int	calculate_new_color(t_lstobject *object, t_lstobject *lights, t_light_vector *l_vector);
int	trace_ray(t_vector direction, t_scene *scene);

#endif
