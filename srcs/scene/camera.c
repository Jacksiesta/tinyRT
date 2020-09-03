#include "../../includes/miniRT.h"

t_camera	*new_camera(t_vector *pos, t_vector *rot, int FOV)
{
	t_camera	*camera;
	
	if (!(camera = malloc(sizeof(t_camera))))
		return (NULL);
	camera->rotation = rot;
	camera->origin = pos;
	camera->FOV = FOV;
	return (camera);	
}
