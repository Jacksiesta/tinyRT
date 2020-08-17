#include "../includes/lstobjects.h"

t_lstobjects		*new_obj(int type, void *object)
{
	t_lstobjects *obj;
	
	obj = malloc(sizeof(t_lstobjects));
	obj->type = type;
	obj->object = object;
	obj->next = NULL;
	return (obj);
}

