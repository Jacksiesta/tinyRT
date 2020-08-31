#include "../../includes/miniRT.h"

int	choice_parsing(t_scene **scene, char *line)
{
	(void)scene;
	if (line[0] != '\0')
	{
		if (line[0] == 'R')
			printf("yez\n");
		if (line[0] == 'A')
			printf("yez\n");
		if (line[0] == 'c')
			printf("yez\n");
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
		if (choice_parsing(scene, line) < 0)
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
		if (choice_parsing(scene, line) < 0)
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
	if (x += r > 0 && line[x] != ' ' && line[x] != '\t')
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
