#include "../../includes/miniRT.h"

int	choice_parsing(t_scene **scene, char *line)
{
	(void)scene;
	if (line[0] != '\0')
	{
		printf("line[0] is [[[%c]]]", line[0]);
		if (line[0] == 'R')
			return (parsing_resolution(scene, line));
		else if (line[0] == 'A')
			return (parsing_ambiant_light(scene, line));
		else if (line[0] == 'c' && line[1] == 'y')
			return (parsing_cylinder(scene, line));
		else if (line[0] == 'c')
		{
			printf("in parsing camera --   \n");
			return (parsing_camera(scene, line));
		}
		else if (line[0] == 'l')
			printf("yez\n");
		else if (line[0] == 's' && line[1] == 'p')
			return (parsing_sphere(scene, line));
		else if (line[0] == 'p' && line[1] == 'l')
			return (parsing_plan(scene, line));
		else if (line[0] == 's' && line[1] == 'q')
			return (parsing_square(scene, line));
		else if (line[0] == 't' && line[1] == 'r')
			return (parsing_triangle(scene, line));
		else
			return (-1);	
	}
	return (0);
}

t_scene	*parsing(int fd)
{
	int		ret;
	char		*line;
	t_scene 	*scene;

	scene = new_empty_scene(BACKGROUND_COLOR);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("OUIOUI\n");
		if (choice_parsing(&scene, line) < 0)
		{
			free(line);
			return (NULL);
		}
		printf("\n");
		free(line);
	}
	if (ret < 0 || choice_parsing(&scene, line) < 0)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (scene);
}

int	parsing_resolution(t_scene **scene, char *line)
{
	int	x;
	int	r;
	int	res_x;
	int	res_y;

	x = 1; // start after identifier letter
	//res_x = 0;
	//res_y = 0;
	if (line[x] != ' ' && line[x] != '\t')
		return (-1);
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	if (line[x] < '0' || line[x] > '9' || (r = ft_atoi(&line[x], &res_x)) < 0)
		return (-1);
	if ((x += r) > 0 && line[x] != ' ' && line[x] != '\t')
		return (-1);
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	if (line[x] < '0' || line[x] > '9' || (r = ft_atoi(&line[x], &res_y)) < 0)
		return (-1);
	x += r;
	while (line[x] == ' ' || line[x] == '\t')
		if (line[++x] && line[x] != ' ' && line[x] != '\t')
			return (-1);
	printf("viewport_working\n");
	return (!((*scene)->viewport = new_canvas(res_x, res_y, 1)) ? -1 : 0);
}

int	parsing_ambiant_light(t_scene **scene, char *line)
{
	int 	x;
	int	r;
	float	intensity;
	int	color;
	
	x = 1;
	if (line[x] != ' ' && line[x] != '\t')
		return (-1);
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	if (line[x] < '0' || line[x] > '9' || (r = ft_atof(&line[x], &intensity) < 0))
		return (-1);
	if ((x += r) > 0 && line[x] != ' ' && line[x] != '\t')
		return (-1);
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	if (line[x] < '0' || line[x] > '9' || (r = ft_atoc(&line[x], &color) < 0))
		return (-1);
	x += r;
	while (line[x] == ' ' || line[x] == '\t')
		if (line[++x] && line[x] != ' ' && line[x] != '\t')
			return (-1);
	//if (add_back(&(*scene)->lights, TYPE_LIGHT, new_default_light(TYPE_AMBIENT, intensity, color)))
	//	return (0);
	//return (-1);
	return ((!(add_back(&(*scene)->lights, TYPE_LIGHT, new_default_light(TYPE_AMBIENT, intensity, color)))) ? 0 : -1);
}

int		parsing_camera(t_scene **scene, char *line)
{
	int			i;
	int			r;
	int			n;
	t_vector	*vectors[2];
	int			fov;

	i = 1;
	r = 0;
	n = -1;
	printf("in camera\n");
	while (++n < 4 && (i += r) && line[i] && (line[i] == ' ' || line[i] == '\t'))
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if ((n < 2) && (((line[i] < '0' || line[i] > '9') && line[i] != '-') ||
		(r = ft_atov(&line[i], &vectors[n])) < 0))
			return (mult_free_ret(vectors, n - 1));
		if ((n == 2) && ((line[i] < '0' || line[i] > '9') ||
		(r = ft_atoi(&line[i], &fov)) < 0))
			return (mult_free_ret(vectors, 2));
	}
	if (line[i] && line[i] != ' ' && line[i] != '\t')
		return (mult_free_ret(vectors, 2));
	printf("camera_working");
	return ((!(add_back(&(*scene)->camera, TYPE_CAMERA, new_camera(
vectors[0], vectors[1], fov))) ? 0 : -1));
}



/*
int	parsing_camera(t_scene **scene, char *line)
{
	int		x;
	int		r;
	int		n;
	int		FOV; // Field Of View
	t_vector	*vec[2];

	x = 1;
	n = -1;
	r = 0;
	printf("in camera\n");
	while ((n++ < 4) && (x += r) && (line[x] == ' ' || line[x] == '\t'))
	{
		while (line[x] == ' ' || line[x] == '\t')
			x++;
		if (n < 2 && (line[x] < '0' || line[x] > '9') && line[x] != '-' && (r = ft_atov(&line[x], &vec[n]) < 0))
		{
			printf("free?\n");
			return (mult_free_ret(vec, n - 1));
		}
		if (n == 2 && (line[x] < '0' || line[x] > '9') && (r = ft_atoi(&line[x], &FOV) < 0))
		{
			printf("freee?\n");
			return (mult_free_ret(vec, 2));
		}
	}
	printf("vec1[%f, %f, %f]", vec[0]->x, vec[0]->y, vec[0]->z);
	printf("oui\n");
	if (line[x] && line[x] != ' ' && line[x] != '\t')
	{
		printf("please\n");
		return (mult_free_ret(vec, 2));
	}
	printf("BLABKA\n");
	//if (add_back(&(*scene)->camera, TYPE_CAMERA, new_camera(vec[0], vec[1], FOV)))
	//	return (0);
	//return (mult_free_ret(vec, 2));
	return ((!(add_back(&(*scene)->camera, TYPE_CAMERA, new_camera(vec[0], vec[1], FOV))) ? 0 : mult_free_ret(vec, 2)));
}*/

//int	parsing_light(t_scene **scene, char *line)
