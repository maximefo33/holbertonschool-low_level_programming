#include "lists.h"
#include <stdlib.h>
#include <string.h>

/**
 * add_node - adds a new node at the beginning of a list
 * @head: pointer to the address of the first node
 * @str: string to duplicate and store in the new node
 *
 * Description: allocates memory for a new node, duplicates
 * the string and inserts the node at the beginning of the list
 *
 * Return: pointer to the new node, or NULL if it fails
 */

list_t *add_node_end(list_t **head, const char *str)
{
	list_t *m, *current;
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

	if (*head == NULL)
	{

		return (NULL);
	}

	current = *head;

	while (current->next != NULL)
	{

		current = current->next;
	}

	m->str = copy;
	m->len = i;
	m->next = NULL;
	current->next = m;

	return (m);
}
