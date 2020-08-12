#include "minilibx_opengl_20191021/mlx.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct 	s_pos
{
	double x;
	double y;
	double z;
}		t_pos;

typedef struct	s_pos2d
{
	double x;
	double y;	
}		t_pos2d;

typedef struct	s_ray
{
	t_pos position;
	t_pos direction;	
}		t_ray;

typedef struct	s_sphere
{
	t_pos 	*center;
	float 	radius;
	int	color;
}		t_sphere;

typedef struct	s_canvas
{
	double	width;
	double	height;
	double	distance;	
}		t_canvas;

typedef struct s_lstobject
{
	int	type;
	void	*object;
	void	*next;	
}		t_lstobject;

t_lstobject	*create_obj(int t, void *o)
{
	t_lstobject	*obj;
	
	obj = malloc(sizeof(t_lstobject));
	obj->type = t;
	obj->object = o;
	obj->next = NULL;
	return (obj);	
}

// insert (x,y,z) values in t_pos variable + ret pos
t_pos		*create_pos(double x, double y, double z)
{
	t_pos	*position;
	
	position = malloc(sizeof(t_pos));
	position->x = x;
	position->y = y;
	position->z = z;
	return (position);	
}

// insert (x,y) values in t_pos2d variable + ret pos
t_pos2d		*create_pos2d(int x, int y)
{
	t_pos2d	*position;
	
	position = malloc(sizeof(t_pos2d));
	position->x = x;
	position->y = y;
	return (position);	
}

// changes *position's (x,y,z) values
void		set_pos(t_pos *position, double x, double y, double z)
{
	position->x = x;
	position->y = y;
	position->z = z;
}

t_sphere	*create_sphere(int radius, int color)
{
	t_sphere	*sphere;
	
	sphere = malloc(sizeof(t_sphere));
	sphere->radius = radius;
	sphere->color = color;
	sphere->center = create_pos(0, 0, 0);
	return (sphere);
}

t_canvas	*create_canvas(int w, int h, int d)
{
	t_canvas	*canvas;
	
	canvas = malloc(sizeof(t_canvas));
	canvas->width = w;
	canvas->height = h;
	canvas->distance = d;
	return (canvas);	
}

int		dot_product(t_pos pos1, t_pos pos2)
{
	return (pos1.x * pos2.x + pos1.y * pos2.y + pos1.z * pos2.z);
}

t_pos		vectorSub(t_pos *v1, t_pos *v2)
{
	t_pos result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
	return (result);	
}
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
	printf("nb is %f\n", x);
	i = (1 << 29) + (i >> 1) - (1 << 22);
	j = 0.5f * (j + x/j);
	j = 0.5f * (j + x/j);
	return (j);
}

// returns (x,y) of intersections
float		intersect(t_pos obs, t_pos pixel, t_sphere *sphere)
{
	t_pos		*difference;
	float		k[3];
	float		discr;
	//t_sphere	sphere;
	t_pos2d		*ret;
	float		r1;
	float		r2;
	
	//sphere = *(t_sphere*)(s);
	printf("\npixel x is %f\n", pixel.x);
	printf("pixel y is %f\n", pixel.y);
	//printf("pixel z is %f\n", pixel.z);
	difference = create_pos(obs.x - sphere->center->x, obs.y - sphere->center->y, obs.z - sphere->center->z);
	printf("difference is %f && %f\n", difference->x, difference->y);
	k[0] = dot_product(pixel, pixel); //A
	k[1] = 2 * dot_product(*difference, pixel); //B
	k[2] = dot_product(*difference, *difference) - (sphere->radius * sphere->radius); //C
	
	discr = k[1] * k[1] - 4 * k[0] * k[2]; // B * B - 4 * A * C
	printf("A is %f\n", k[0]);
	printf("B is %f\n", k[1]);
	printf("C is %f\n", k[2]);
	printf("discr is %f\n", discr);
	free(difference);
	if (discr < 0) // no intersection
		return (0);
	r1 = (-k[1] + ft_squrt_bin(discr) / (2 * k[0]));
	r2 = (-k[1] - ft_squrt_bin(discr) / (2 * k[0]));

	printf("r1 is %f\n", r1);
	printf("r2 is %f\n", r2);
	if (r1 < r2)
		return (r1);
	return (r2);
}

int main(void)
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_pos		*obs_pos;
	t_pos		*pix;
	t_pos2d		*pos2d;
	t_canvas	*viewport;
	t_sphere	*sphere;
	int		x;
	int		y;
	float		root;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 100, 100, "WOW");
	viewport = create_canvas(100, 100, 1);

	obs_pos = create_pos(0, 0, 0);
	sphere = create_sphere(30, 0xff0000);
	set_pos(sphere->center, 30, 30, 31);
	x = 0;
	while (x < 100)
	{
		y = 0;
		while (y < 100)
		{
			pix = create_pos(x, y, viewport->distance);
			root = intersect(*obs_pos, *pix, sphere);
			printf("root is %f\n", root);
			if (root)
			{
				printf("IM IN ROOT YAY\n");
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, sphere->color);
			}
			else
			{
				printf("im in black\n");
				mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x0);
			}
			y++;
		}
		x++;
	}
	mlx_loop(mlx_ptr);	
}

