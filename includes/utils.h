#ifndef UTILS_H
# define UTILS_H

int	ft_atoi(char *line, int *num);
int	ft_atoc(char *line, int *color);
int	ft_atov(char *line, t_vector **v1);
int	ft_atof(char *line, float *num);

/** LEAKS **/
int	free_and_ret_minus_one(void *ptr);
int	mult_free_ret(t_vector *ptr[], int size);

#endif
