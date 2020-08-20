#ifndef RAYTRACING_H
# define RAYTRACING_H

float	compute_lighting(t_vector *point, t_vector *normal, t_lstobject *lights);
float	intersect_sphere(t_vector obs, t_vector direction, t_sphere *object);
int	calculate_new_color(int type, t_lstobject *object, t_lstobject *lights, t_vector *point);
int	trace_ray(t_vector origin, t_vector direction, t_lstobject *objects, t_lstobject *lights);

#endif
