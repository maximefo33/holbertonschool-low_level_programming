#include "lists.h"
#include <stdlib.h>
#include <string.h>

list_t *add_node(list_t **head, const char *str)
{
	list_t *m;
	char *copy;

	if (str == NULL || head == NULL)
	{
		return (NULL);
	}

	m = malloc(sizeof(list_t));
	if (m == NULL)
	{
		return (NULL);
	}

	copy = strdup(str);

	if (copy == NULL)
	{

		free(m);
		return (NULL);
	}

	m->str = copy;
	m->len = strlen(copy);
	m->next = *head;
	*head = m;

	return (m);
}