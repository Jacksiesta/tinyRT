#include "../../includes/miniRT.h"

int	parsing_sphere(t_scene **scene, char *line)
{
	t_vector	*center;
	float		radius;
	int		color;
	int		x[3];
	
	x[0] = 2; // pos in line
	x[1] = -1; // group ([1 ; 3])
	x[2] = 0; // lenght of given group
	while (++x[1] < 4 && (x[0] += x[2]) && (line[x[0]] == ' ' || line[x[0]] == '\t'))
	{
		while (line[x[0]] == ' ' || line[x[0]] == '\t')
			x[0]++;
		// first group aka (x,y,z) pos of center
		if (!x[1] && ((line[x[0]] < '0' || line[x[0]] > '9') && line[x[0]] != '-')) || ((x[2] = ft_atof(&line[x[0]], &center)) < 0)
			return (-1);
		// second group aka radius
		if ((x[1] == 1) && ((line[x[0]] < '0' || line[x[0]] > '9') || (x[2] = ft_atof(&line[x[0]], &radius)) < 0))
			return (free_and_ret_minus_one(center));
		// third group aka color
		if ((x[1] == 2) && ((line[x[0]] < '0' || line[x[0]] > '9') || (x[2] = ft_atoc(&line[x[0]], &color)) < 0))
			return (free_and_ret_minus_one(center));
	}		
	if (line[x[0]] && line[x[0]] != ' ' && line[x[0]] != '\t')
		return (free_and_ret_minus_one(center));
	if (!line[x[0]] && (!(add_back(&(*scene)->object, TYPE_SPHERE, new_sphere(radius, color, 10, center)))))
		return (0)
	return (free_and_ret_minus_one(center));
	//return (!l[i[0]] && (!(add_back(&(*scene)->objects, TYPE_SPHERE, new_sphere(radius, color, 10, center))) ? 0 : free_and_return_minus_one(center)));
}

// pl  0.0,0.0,0.0  0.0,0.0,1.0  0,0,255
//      pos point    3d orient    color
int		parsing_plan(t_scene **scene, char *line)
{
	int		x;
	int		y;
	int		n;
	int		color;
	t_vector	*v[2];

	x = 0; //pos in line
	n = -1; // group [1 ; 3]
	y = 0; // length of given group
		
	while (++n < 4 && (x += y) > 0 && line[x] == ' ' || line[x] == '\t')
	{
		while(line[x] == ' ' || line[x] == '\t')
			x++;
		// first two groups
		if ((n < 2) && (((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = atov(&line[x], &v[n])) < 0))
			return (mult_free_ret(v, n - 1));
		// 3rd group aka color
		if ((n == 2) && ((line[x] < '0' || line[x] > '9') || (y = atoc(&line[x], &color)) < 0))
			return (mult_free_ret(v, 2));		
	}
	if (line[x] && line[x] != ' ' && line[x] != '\t')
		return (mult_free_ret(v, 2));
	if (!(add_back(&(*scene)->object, TYPE_PLAN, new_plan(v[0], v[1], color))))
		return (0);
	return (mult_free_ret(v, 2));
	//return ((!(add_back(&(*scene)->objects, TYPE_PLAN, new_plan(vectors[0], vectors[1], color))) ? 0 : multiple_free_return(vectors, 2)));
}

// sq  0.0,0.0,20.6   1.0,0.0,0.0   12.6   255,0,255
//	center		3d orient    h	    color
int		parsing_square(t_scene **scene, char *line)
{
	int 		x;
	int		y;
	int		n;
	int		color;
	float		h;
	t_vector	*v[2];

	x = 2;
	n = -1;
	y = 0;
	while (++n < 5 && (x += y) && (line[x] == ' ' || line[x] == '\t'))
	{
		while (line[x] == ' ' || line[x] == '\t')
			x++;
		// group 1 && 2
		if ((n < 2) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atov(&line[x], &v[n]) < 0)
			return (mult_free_ret(v, n - 1));
		// group 3 aka height
		if ((n == 2) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atof(&line[x], &h)) < 0)
			return (mult_free_ret(v, 2));
		// group 4 aka colour
		if ((n == 3) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atoc(&line[x], &color)) < 0)
			return (mult_free_ret(v, 2)); 	
	}
	if (line[x] && line[x] != ' ' && line[x] != '\t')
		return (mult_free_ret(v, 2));
	if (!(add_back(&(*scene)->object, TYPE_SQUARE, new_square(v[0], v[1], h, color))))
		return (0);
	return (mult_free_ret(v, 2));
	//return ((!(add_back(&(*scene)->objects, TYPE_SQUARE, new_square(vectors[0], vectors[1], size, i[3]))) ? 0 : multiple_free_return(vectors, 2)));
}

// tr  10.0,20.0,10.0   10.0,10.0,20.0   20.0,10.0,10.0   0,255,255
//	 pos point1	  pos point2	  pos point3	    color
int		parsing_triangle(t_scene *scene, char *line)
{
	int		x;
	int		y;
	int 		n;
	int 		color;
	t_vector	*v[3];

	x = 2;
	y = 0;
	n = -1;
	while ((++n < 5) && (x += y) && (line[x] == ' ' || line[x] == '\t'))
	{
		while (line[x] == ' ' || line[x] == '\t')
			x++;
		// all 3 points
		if ((n < 3) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atov(&line[x], &v[n])) < 0)
			return (mult_free_ret(v, n - 1));
		if ((n == 3) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atoc(&line[x], color)) < 0)
			return (mult_free_ret(v, 3));	
	}
	if (line[x] && line[x] != ' ' && line[x] != '\t')
		return (mult_free_ret(v, 3));
	if (!(add_back(&(*scene)->object, TYPE_TRIANGLE, new_triangle(v[0], v[1], v[2], color))))
		return (0);
	return (mult_free_ret(v, 3));
	//return ((!(add_back(&(*scene)->objects, TYPE_TRIANGLE, new_triangle(vec[0], vec[1], vec[2], i[3]))) ? 0 : multiple_free_return(vec, 2)));
}

// cy	50.0,0.0,20.6	0.0,0.0,1.0	14.2	21.42	10,0,255
//	    center	3d orient	diam	h	color
int		parsing_cylinder(t_scene **scene, char *line)
{
	int		x;
	int		y;
	int		n;
	int		h;
	int		d;
	int		color;
	t_vector	*v[2];

	x = 2;
	y = 0;
	n = -1;
	while ((++n < 6) && (x += y) && (line[x] == ' ' || line[] == '\t'))
	{
		while (line[x] == ' ' || line[x] == '\t')
			x++;
		// group 1 && 2
		if ((n < 2) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atov(&line[x], &v[n])) < 0)
			return (mult_free_ret(v, n - 1));
		if ((n == 2) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atof(&line[x], &d)) < 0)
			return (mult_free_ret(v, 2));
		if ((n == 3) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atof(&line[x], &h)) < 0)
			return (mult_free_ret(v, 2));
		if ((n == 4) && ((line[x] < '0' || line[x] > '9') && line[x] != '-') || (y = ft_atoc(&line[x], &color)) < 0)
			return (mult_free_ret(v, 2));		
	}
	if (line[x] && line[x] != ' ' && line[x] != '\t')
		return (mult_free_ret(v, 2));
	if (!(add_back(&(*scene)->object, TYPE_CYLINDER, new_cylinder(v[0], v[1], d, h, color))))
		return (0);
	return (mult_free_ret(v, 2));
	
}
