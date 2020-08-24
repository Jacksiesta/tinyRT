#include "../includes/miniRT.h"

t_rotation	*new_rotation(t_vector *rota_x, t_vector *rota_y, t_vector *rota_z)
{
	t_rotation	*rotation;
	
	rotation = malloc(sizeof(t_rotation));
	rotation->x = rota_x;
	rotation->y = rota_y;
	rotation->z = rota_z;
	return (rotation);	
}

/*
void		rot(t_vector *v, t_vector *angle)
{
		
}*/
