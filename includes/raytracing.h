#ifndef RAYTRACING_H
# define RAYTRACING_H

float	compute_lighting(t_vector *point, t_vector *normal, t_lstobjects *lights);
float	intersect_sphere(t_vector obs, t_vector direction, t_sphere *object);
int	trace_ray(t_vector origin, t_vector direction, t_lstobjects *objects, float t_min_max[2], t_lstobjects *lights);


#endif
