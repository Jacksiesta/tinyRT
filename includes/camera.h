#ifndef CAMERA_H
# define CAMERA_H

typedef struct		s_camera
{
	t_vector	*origin;
	t_vector	*rotation;	
	int		FOV;
}			t_camera;

t_camera	*new_camera(t_vector *pos, t_vector *rot, int FOV);

#endif
