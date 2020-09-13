#ifndef PARSING_H
# define PARSING_H

int	choice_parsing(t_scene **scene, char *line);
t_scene	*parsing(int fd);
int	parsing_resolution(t_scene **scene, char *line);
int	parsing_ambiant_light(t_scene **scene, char *line);
int	parsing_camera(t_scene **scene, char *line);
int	parsing_sphere(t_scene **scene, char *line);
int	parsing_plan(t_scene **scene, char *line);
int	parsing_square(t_scene **scene, char *line);
int	parsing_triangle(t_scene **scene, char *line);
int	parsing_cylinder(t_scene **scene, char *line);

#endif
