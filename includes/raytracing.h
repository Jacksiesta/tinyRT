#ifndef RAYTRACING_H
# define RAYTRACING_H

#include "scene.h"

//float	compute_lighting(t_light_vector *l_vector, t_lstobject *lights);
//int	calculate_new_color(t_lstobject *object, t_lstobject *lights, t_light_vector *l_vector);
//int	trace_ray(t_vector direction, t_scene *scene);
t_vector	*reflect_ray(t_vector v1, t_vector v2);
int			color_with_reflect(t_lstobject *closest_object, t_scene *scene, t_light_vector *l_vectors, int color);
int			calculate_new_color(t_lstobject *objects, t_lstobject *lights, t_light_vector *l_vectors, t_scene *scene);
int			set_l_vec_and_calc(t_lstobject *closest_object, t_vector direction, float closest_t, t_scene *scene);
float		closest_inters(t_vector origin, t_vector direction, t_scene *scene, t_lstobject **closest_object);
int			trace_ray(t_vector direction, t_scene *scene);


#endif
