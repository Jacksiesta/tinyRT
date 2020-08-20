#ifndef SCENE_H
# define SCENE_H

typedef struct 	s_scene
{
	t_vector	*origin;
	t_lstobject	*objects;
	t_lstobject	*lights;
	int		background_color;
	float		t_min;
	float		t_max;		
}			t_scene;



#endif
