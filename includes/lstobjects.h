#ifndef LSTOBJECTS_H
# define LSTOBJECTS_H

#include <stdlib.h>

# define TYPE_SPHERE 0
# define TYPE_PLAN 1
# define TYPE_LIGHT 2
# define TYPE_SQUARE 3
# define TYPE_TRIANGLE 4
# define TYPE_CYLINDER 5

typedef struct s_lstobject
{
	int	type;
	void	*object;
	void	*next;	
}		t_lstobject;

t_lstobject	*new_obj(int type, void *object);

#endif
