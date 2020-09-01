#include "../includes/lstobjects.h"

t_lstobject		*new_obj(int type, void *object)
{
	t_lstobject *obj;
	
	if (!(obj = malloc(sizeof(t_lstobject))))
		return (NULL);
	obj->type = type;
	obj->object = object;
	obj->next = NULL;
	return (obj);
}

int			add_back(t_lstobject **lst, int type, void *object)
{
	t_lstobejct	*start;
	
	if (!object)
		return (-1);
	start = *lst;
	if (start)
	{
		while (start->next)
			start = start->next; //incr
		if (!(start->next = new_obj(type, object)))
			return (-1);	
	}	
	else
		*lst = new_obj(type, object);
	return (0);
}
