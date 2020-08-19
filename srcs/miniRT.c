#include "../includes/miniRT.h"
//#include "miniRT.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

/*
double		ft_squrt_bin(double nb, int p)
{
	int 	left;
	int 	right;
	double 	mid;
	float 	res;
	printf("Number nb is %f\n", nb);
	if (nb == 0)
		return (0);
	right = nb;
	left = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (mid * mid == nb || mid * mid < nb)
		{
			res = mid;
			if (mid * mid == nb)
				break;
			else
				left = mid + 1;
		}
		else
			right = mid - 1;
	}
	left = 0;
	mid = 0.1;
	while (left++ < p)
	{
		while (res * res <= nb)
			res += mid;
		res -= mid;
		mid /= 10;
		printf("mid is %f[%i]\n", mid, left);
		printf("res is %f[%i]\n", res, left);
	}
	return (res);
}*/

float	ft_squrt_bin(float x)
{
	int	i;
	float j;

	j = x;
	i = (1 << 29) + (i >> 1) - (1 << 22);
	j = 0.5f * (j + x/j);
	j = 0.5f * (j + x/j);
	return (j);
}

int		main(void)
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_canvas		*viewport;
	t_vector		*obs;
	t_vector		*direction;
	t_lstobject		*lstobj;
	t_lstobject		*lstlight;
	int			color;
	int			x;
	int			y;
	float			t_min_max[2];

	/**	WINDOW **/
	mlx_ptr = mlx_init();
	viewport = new_canvas(500, 500, 1);
	win_ptr = mlx_new_window(mlx_ptr, viewport->width, viewport->height, "miniRT");
	/** SPHERES & O **/
	obs = new_vector(0, 0, -5);
	lstobj = new_obj(TYPE_SPHERE, new_default_sphere(1, 0xff0074));
	set_vector(((t_sphere *)lstobj->object)->center, 0, -1, 5);
	lstobj->next = new_obj(TYPE_SPHERE, new_default_sphere(1, 0x00cccc));
	set_vector(((t_sphere *)((t_lstobject *)lstobj->next)->object)->center, 2, -2, 8);
	((t_lstobject *)lstobj->next)->next = new_obj(TYPE_SPHERE, new_default_sphere(1, 0xf1c40f));
	set_vector(((t_sphere *)((t_lstobject *)((t_lstobject *)lstobj->next)->next)->object)->center, -2, 2, 4);
	/** LIGHTS **/
	lstlight = new_obj(TYPE_LIGHT, new_default_light(TYPE_AMBIENT, 0.1));
	lstlight->next = (t_lstobject *)new_obj(TYPE_LIGHT, new_default_light(TYPE_POINT, 0.5));
	set_vector(((t_light *)((t_lstobject *)lstlight->next)->object)->vector, -3, 1, 0);
	((t_lstobject *)lstlight->next)->next = new_obj(TYPE_LIGHT, new_default_light(TYPE_DIRECTIONAL, 0.8));
	set_vector(((t_light *)((t_lstobject *)((t_lstobject *)lstlight->next)->next)->object)->vector, 1, -2, -1);
	/** RENDERING **/
	x = -(viewport->width/2) + 1;
	while ((x + (viewport->width/2) <= viewport->width))
	{
		y = -(viewport->height/2);
		while (y < viewport->height/2)
		{
			t_min_max[0] = 1;
			t_min_max[1] = -1;
			direction = new_vector(x / viewport->width, y / viewport->height, 1);
			color = trace_ray(*obs, *direction, lstobj, t_min_max, lstlight);
			if (color != BACKGROUND_COLOR)
				mlx_pixel_put(mlx_ptr, win_ptr, (int)(x + (viewport->width/2)), (int)(y + (viewport->height/2)), (int)color);
			y++;
		}
		x++;
	}
	mlx_loop(mlx_ptr);
}
