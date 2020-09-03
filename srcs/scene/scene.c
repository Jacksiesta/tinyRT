#include "../../includes/miniRT.h"

t_scene		*new_scene(t_lstobject *camera, t_lstobject *objects, t_lstobject *lights, int color)
{
	t_scene	*scene;	
	
	scene = malloc(sizeof(t_scene));
	//scene->origin = origin;
	scene->viewport = NULL;
	scene->viewplane = NULL;
	//scene->camera = camera;
	scene->objects = objects;
	scene->lights = lights;
	scene->background_color = color;
	scene->t_min = 0.001;
	scene->t_max = -1;
	scene->depth = 3;
	return (scene);
}

t_scene		*new_empty_scene(int color)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	scene->origin = NULL;
	scene->objects = NULL;
	scene->lights = NULL;
	scene->background_color = color;
	scene->t_min = 0.001;
	scene->t_max = -1;
	return (scene);
}
