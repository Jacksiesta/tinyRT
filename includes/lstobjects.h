#ifndef LSTOBJECTS_H
# define LSTOBJECTS_H

#include <stdlib.h>

# define TYPE_SPHERE 0
# define TYPE_PLAN 1
# define TYPE_LIGHT 2

typedef struct s_lstobjects
{
	int	type;
	void	*object;
	void	*next;	
}		t_lstobjects;

t_lstobjects	*new_obj(int type, void *object);

#endif
