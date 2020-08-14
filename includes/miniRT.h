#ifndef MINI_RT
# define MINI_RT

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "minilibx_opengl_20191021/mlx.h"
#include "mlx.h"
#include "sphere.h"

/*
typedef struct	s_sphere
{
	t_pos 	*center;
	float 	radius;
	int	color;
}		t_sphere;*/

t_lstobject	*create_obj(int t, void *o);
t_pos		*create_pos(double x, double y, double z);
t_pos2d		*create_pos2d(int x, int y);
void		set_pos(t_pos *position, double x, double y, double z);
//t_sphere	*create_sphere(int radius, int color);
t_canvas	*create_canvas(int w, int h, int d);
int		dot_product(t_pos pos1, t_pos pos2);
t_pos		vectorSub(t_pos *v1, t_pos *v2);
float		ft_squrt_bin(float x);
float		intersect(t_pos obs, t_pos pixel, t_sphere *sphere);


#endif
