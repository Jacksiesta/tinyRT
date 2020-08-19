#include "../includes/lstobjects.h"

t_lstobject		*new_obj(int type, void *object)
{
	t_lstobject *obj;
	
	obj = malloc(sizeof(t_lstobject));
	obj->type = type;
	obj->object = object;
	obj->next = NULL;
	return (obj);
}

