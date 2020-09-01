#ifndef UTILS_H
# define UTILS_H

int	ft_atoi(char *line, int *num);

/** LEAKS **/
int	free_and_ret_minus_one(void *ptr);
int	multiple_free_return(t_vector *ptr[], int size);

#endif
