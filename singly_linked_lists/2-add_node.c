#include "lists.h"
#include <stdlib.h>
#include <string.h>

/**
 * add_node - Adds a new node at the beginning of a list_t list
 * @head: Double pointer to the head of the list
 * @str: String to duplicate and store in the new node
 *
 * Return: Address of the new node, or NULL if it fails
 */

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
