#include "../includes/miniRT.h"

t_camera	*new_camera(t_vector *pos, t_vector *rot)
{
	t_camera	*camera;
	
	camera = malloc(sizeof(t_camera));
	camera->rotation = rot;
	camera->origin = pos;
	return (camera);	
}
