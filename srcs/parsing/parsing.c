#include "../../includes/miniRT.h"

int	choice_parsing(t_scene **scene, char *line)
{
	(void)scene;
	if (line[0] != '\0')
	{
		if (line[0] == 'R')
			return (parsing_resolution(scene, line));
		if (line[0] == 'A')
			return (parsing_ambiant_light(scene, line));
		if (line[0] == 'c')
			return (parsing_camera(scene, line));
		if (line[0] == 'l')
			printf("yez\n");
		if (line[0] == 's' && line[1] == 'p')
			printf("yez\n");
		if (line[0] == 'p' && line[1] == 'l')
			printf("yez\n");
		if (line[0] == 's' && line[1] == 'q')
			printf("yez\n");
		if (line[0] == 'c' && line[1] == 'y')
			printf("yez\n");
		if (line[0] == 't' && line[1] == 'r')
			printf("yez\n");
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
	while ((ret = get_next_line(fd, &line)))
	{
		if (choice_parsing(&scene, line) < 0)
		{
			free(line);
			return (NULL);
		}
		free(line);
	}
	if (ret < 0)
		return (NULL);
	else
	{
		if (choice_parsing(&scene, line) < 0)
		{
			free(line);
			return (NULL);
		}
		free(line);
	}
	return (scene);
}

int	parsing_resolution(t_scene **scene, char *line)
{
	int	x;
	int	r;
	int	res_x;
	int	res_y;

	x = 1; // start after identifier letter
	res_x = 0;
	res_y = 0;
	if (line[x] != ' ' || line[x] != '\t')
		return (-1);
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	if (line[x] < '0' || line[x] > '9' || (r = ft_atoi(&line[x], &res_x)) < 0)
		return (-1);
	if ((x += r > 0) && line[x] != ' ' && line[x] != '\t')
		return (-1);
	while (line[x] == ' ' || line[x] == '\t')
		x++;
	if (line[x] < '0' || line[x] > '9' || (r = ft_atoi(&line[x], &res_y)) < 0)
		return (-1);
	x += r;
	while (line[x] == ' ' || line[x] == '\t')
		if (line[++x] && line[x] != ' ' && line[x] != '\t')
			return (-1);
	return (!((*scene)->viewport = new_canvas(res_x, res_y, 1)) ? -1 : 0);
}

int	parsing_ambiant_light(t_scene **scene, char *line)
{
	int 	x;
	int	r;
	float	intensity;
	int	color;
	
	x = 1;
	if (line[x] != ' ' || line[x] != '\t')
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
	while ((n++ < 4) && (x += r) && (line[x] == ' ' || line[x] == '\t'))
	{
		while (line[x] == ' ' || line[x] == '\t')
			x++;
		if (n < 2 && (line[x] < '0' || line[x] > '9') && line[x] != '-' && (r = ft_atov(&line[x], &vec) < 0))
			return (mult_free_ret(vec, n - 1));
		if (n == 2 && (line[x] < '0' || line[x] > '9') && (r = ft_atoi(&line[x], &FOV) < 0))
			return (mult_free_ret(vec, 2));
	}
	if (line[x] && line[x] != ' ' || line[x] != '\t')
		return (mult_free_ret(vec, 2));
	//if (add_back(&(*scene)->camera, TYPE_CAMERA, new_camera(vec[0], vec[1], FOV)))
	//	return (0);
	//return (mult_free_ret(vec, 2));
	return ((!(add_back(&(*scene)->camera, TYPE_CAMERA, new_camera(vec[0], vec[1], FOV))) ? 0 : mult_free_ret(vec, 2)));
}

//int	parsing_light(t_scene **scene, char *line)
