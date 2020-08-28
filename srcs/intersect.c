#include "../includes/miniRT.h"

float	intersect_plan(t_vector origin, t_vector direction, t_plan *object)
{
	float	temp;
	float	A;
	float	B;
	float	touch;
	
	touch = 0;
	temp = dot_vector(*object->normal, *object->point);
	A = temp - dot_vector(origin, *object->normal);
	B = dot_vector(direction, *object->normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	printf("touch is %f\n", touch);
	return (touch);
}

float	intersect_square(t_vector origin, t_vector direction, t_square *sq)
{
	t_vector	*point;
	t_vector	*ab;
	t_vector	*ac;
	t_vector	*ap;
	t_vector	*normal;
	t_vector	*var;
	float		A;
	float		B;
	float		X;
	float		Y;
	float		temp;
	float		touch;

	ab = sub_vector(*sq->b, *sq->a);
	ac = sub_vector(*sq->c, *sq->a);
	// cross prod of (ab x ac) to get normal 
	normal = new_vector(ab->x * ac->y - ab->y * ac->x, ab->z * ac->x - ab->x * ac->z, ab->y * ac->z - ab->z * ac->y);
	temp = dot_vector(*normal, *sq->center);
	A = temp - dot_vector(origin, *normal);
	B = dot_vector(direction, *normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	var = scale_vector(touch, direction);
	point = add_vector(origin, *var);
	free(var);
	ap = sub_vector(*point, *sq->a);
	X = dot_vector(*ap, *ac) / dot_vector(*ac, *ac);
	Y = dot_vector(*ap, *ab) / dot_vector(*ab, *ab);
	if (X >= 0 && X <= 1 && Y >= 0 && Y <= 1)
		return (touch);
	return (0); 
}
/*
float	intersect_triangle(t_vector origin, t_vector direction, t_triangle *tr)
{
	t_vector	*ab;
	t_vector	*ac;
	t_vector	*normal;
	t_vector	*var;
	t_vector	*point;
	t_vector	*p;
	float		A;
	float		B;
	float		C;
	float		D;
	float		E;
	float		denom;
	float		touch;
	float		r1;
	float		r2;
	
	ab = sub_vector(*tr->b, *tr->a);
	ac = sub_vector(*tr->c, *tr->a);
	//cross prod of (ab x ac) to get normal
	normal = new_vector(ab->x * ac->y - ab->y * ac->x, ab->y * ac->z - ab->z * ac->y, ab->z * ac->x - ab->x * ac->z);
	C = dot_vector(*normal, *tr->a);
	A = C - dot_vector(*normal, *tr->a);
	B = dot_vector(direction, *normal);
	touch = A / B;
	printf("touch is %f\n", touch);
	if (touch < 0)
		return (0);
	var = scale_vector(touch, direction);
	point = add_vector(origin, *var);
	free(var);
	p = sub_vector(*point, *tr->a);
	A = dot_vector(*ab, *ab);
	B = dot_vector(*ab, *ac);
	C = dot_vector(*ac, *ac);
	D = dot_vector(*p, *ab);
	E = dot_vector(*p, *ac);
	denom = B * B - A * C;
	r1 = (B * E - C * D) / denom;
	if (r1 < 0 || r1 > 1)
		return (0);
	r2 = (B * D - A * E) / denom;
		return (0);
	return (touch);
}*/

float		intersect_triangle(t_vector origin, t_vector direction, t_triangle *tr)
{
	t_vector 	*point;
	t_vector 	*temp;
	float 		denom;
	float 		A;
	float		B;
	float 		touch;
	t_vector 	*u;
	t_vector 	*v;
	t_vector 	*w;
	t_vector 	*normal;
	float 		r1;
	float		r2;
	float		uu;
	float		uv;
	float		vv;
	float		wu;
	float		wv;
	
	u = sub_vector(*tr->b, *tr->a);
	v = sub_vector(*tr->c, *tr->a);
	normal = cross_product(*u, *v);
	denom = dot_vector(*normal, *tr->a);
	A = denom - dot_vector(origin, *normal);
	B = dot_vector(direction, *normal);
	touch = A / B;
	if (touch < 0)
		return (0);
	temp = scale_vector(touch, direction);
	point = add_vector(origin, *temp);
	free(temp);
	w = sub_vector(*point, *tr->a);
	uu = dot_vector(*u, *u);
	uv = dot_vector(*u, *v);
	vv = dot_vector(*v, *v);
	wu = dot_vector(*w, *u);
	wv = dot_vector(*w, *v);
	denom = uv * uv - uu * vv;
	r1 = (uv * wv - vv * wu) / denom;
	if (r1 < 0 || r1 > 1)
		return (0);
	r2 = (uv * wu - uu * wv) / denom;
	if (r2 < 0 || (r2 + r1 > 1))
		return (0);
	return (touch);
}

float	intersect_cyl(t_vector origin, t_vector direction, t_cylinder *cy)
{
	float		A;
	float		B;
	float		C;
	float		discr;
	float		root1;
	float		root2;
	float		size;
	float		ret;
	t_vector	*x;
	float		var[4];
	float		d[4];
	t_vector	*tmp;
	t_vector	*tmp2;
	t_vector	*point;
	t_vector	*point_tmp;

	//printf("center is %f %f %f \n", cy->center->x, cy->center->y, cy->center->z);
	//printf("origin is %f %f %f \n", origin.x, origin.y, origin.z);
	x = sub_vector(origin, *cy->center);
	var[0] = 1.0 / dot_vector(*cy->orientation, *cy->orientation);
	var[1] = dot_vector(direction, *cy->orientation);
	var[2] = dot_vector(*x, *x);
	var[3] = dot_vector(*cy->orientation, *x);
	A = dot_vector(direction, direction) - (var[0] * var[1] * var[1]);
	B = 2.0 * (dot_vector(direction, *x)) - (2 * var[0] * var[1] * var[3]);
	C = var[2] - ((cy->diameter / 2) * (cy->diameter / 2.0)) - (var[0] * var[3] * var[3]);
	free(x);
	discr = B * B - 4 * A * C;
	root1 = (-B + sqrt(discr)) / 2 * A;
	root2 = (-B - sqrt(discr)) / 2 * A;
	if (root1 < root2)
		ret = root1;
	else
		ret = root2;
	if (ret == 0)
		return (0);

	size = distance_points(*cy->point1, *cy->point2);
	tmp = scale_vector(ret, direction);
	point = add_vector(origin, *tmp);
	free(tmp);
	/** POINT 1 **/
	discr = dot_vector(*cy->orientation, *cy->point1);
	A = discr - dot_vector(*point, *cy->orientation);
	B = dot_vector(*cy->orientation, *cy->orientation);
	C = A / B;
	tmp = scale_vector(C, *cy->orientation);
	point_tmp = add_vector(*point, *tmp);
	free(tmp);
	d[2] = distance_points(*point, *point_tmp);
	free(point_tmp);

	/** POINT 2 **/
	discr = dot_vector(*cy->orientation, *cy->point2);
	A = discr - dot_vector(*point, *cy->orientation);
	tmp2 = scale_vector(-1, *cy->orientation);
	B = dot_vector(*tmp2, *cy->orientation);
	C = A / B;
	tmp = scale_vector(C, *tmp2);
	point_tmp = add_vector(*point, *tmp);
	free(tmp2);
	free(tmp);
	/** var[3] == dist between points **/
	d[3] = distance_points(*point, *point_tmp);
	free(point_tmp);
	free(point);
	
	/** POINT 1 **/
	C = 0;
	discr = dot_vector(*cy->orientation, *cy->point1);
	A = discr - dot_vector(*point, *cy->orientation);
	B = dot_vector(direction, *cy->orientation);
	C = A / B;
	if (C > 0)
	{
		tmp = scale_vector(C, direction);
		point = add_vector(origin, *tmp);
		free(tmp);
		d[0] = distance_points(*point, *cy->point2);
		d[1] = distance_points(*point, origin);
		if (d[0] < cy->diameter / 2)
		{
			if (!(d[2] > size || d[3] > size))
				return (ret);
			free(point);
			return (C);
		} 	
		free(point);
	}

	/* * POINT 2 **/
	C = 0;
	discr = dot_vector(*cy->orientation, *cy->point2);
	A = discr - dot_vector(*point, *cy->orientation);
	B = dot_vector(direction, *cy->orientation);
	C = A / B;
	if (C > 0)
	{
		tmp = scale_vector(C, direction);
		point = add_vector(origin, *tmp);
		free(tmp);
		d[0] = distance_points(*point, *cy->point1);
		d[1] = distance_points(*point, origin);
		if (d[0] < cy->diameter / 2)
		{
			if (!(d[2] > size || d[3] > size))	
				return (ret);
			free(point);
			return (C);
		}
		free(point);
	}
	if ((d[2] > 0 || d[3] > size))
		return (0);
	printf("ROOT %f\n", ret);
	return (0);





	
}
