#include "lists.h"
#include <stdlib.h>
#include <string.h>

list_t *add_node(list_t **head, const char *str)
{
	list_t *m;
	char *copy;

	int i = 0;

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
	while (copy[i] != '\0')
	{
		i++;
	}

	m->str = copy;
	m->len = i;
	m->next = *head;
	*head = m;

	return (m);
}