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

void		rx(t_vector *v, float x)
{
	t_vector	temp;
	
	temp.x = v->x;
	temp.y = v->y * cos(x) - v->z * sin(x);
	temp.z = v->y * sin(x) + v->z * cos(x);
	*v = temp;	
}

void		ry(t_vector *v, float y)
{
	t_vector	temp;
	
	temp.x = v->x * cos(y) + v->z * sin(y);
	temp.y = v->y;
	temp.z = v->x * -sin(y) + v->z * cos(y);
	*v = temp;	
}

void		rz(t_vector *v, float z)
{
	t_vector	temp;
	
	temp.x = v->x * cos(z) - v->y * sin(z);
	temp.y = v->x * sin(z) + v->y * cos(z);
	temp.z = v->z;
	*v = temp;	
	
}

void		rot(t_vector *v, t_vector *angle)
{
	rx(v, angle->x);
	ry(v, angle->y);
	rz(v, angle->z);
}

void		anti_rot(t_vector *v, t_vector *angle)
{
	rx(v, -angle->x);
	ry(v, -angle->y);
	rz(v, -angle->z);	
}
