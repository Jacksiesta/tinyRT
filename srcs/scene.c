#include "../includes/miniRT.h"

t_scene		*new_scene(t_vector *origin, t_lstobject *objects, t_lstobject *lights, int color)
{
	t_scene	*scene;	
	
	scene = malloc(sizeof(t_scene));
	scene->origin = origin;
	scene->objects = objects;
	scene->lights = lights;
	scene->background_color = color;
	scene->t_min = 1;
	scene->t_max = -1;
	return (scene);

}
