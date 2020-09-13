#ifndef SCENE_H
# define SCENE_H

#include "vector.h"
#include "lstobjects.h"
#include "canvas.h"
#include "miniRT.h"

typedef struct 	s_scene
{
	t_vector	*origin;
	t_lstobject	*objects;
	t_lstobject	*lights;
	int		background_color;
	float		t_min;
	float		t_max;		
	float		depth;
	t_lstobject	*camera;
	t_canvas	*viewplane;
	t_canvas	*viewport;
	
}			t_scene;

t_scene		*new_scene(t_vector *origin, t_lstobject *objects, t_lstobject *lights, int color);
t_scene		*new_empty_scene(int color);


#endif
