#include "../../includes/miniRT.h"

int	free_and_ret_minus_one(void *ptr)
{
	free(*ptr);
	return (-1);	
}

int	multiple_free_return(t_vector *ptr[], int size)
{
	while (size--)
		free(ptr[size]);
	return (-1);	
}
