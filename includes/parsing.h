#ifndef PARSING_H
# define PARSING_H

int	choice_parsing(t_scene **scene, char *line);
t_scene	*parsing(int fd);
int	parsing_resolution(t_scene **scene, char *line);

#endif
