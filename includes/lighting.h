#ifndef LIGHTING_H
# define LIGHTING_H

#include "scene.h"
#include "light.h"

float		calcul_shiny(t_light_vector *l_vectors, t_light *light, float lenght_v, t_vector *vec_l);
t_vector	*type_light(t_light_vector *l_vectors, t_light *light, t_scene *scene);
float		compute_special_lights(t_light_vector *l_vectors, t_light *light, t_scene *scene);
float		compute_lighting(t_light_vector *l_vectors, t_lstobject *lights, t_scene *scene);

#endif
