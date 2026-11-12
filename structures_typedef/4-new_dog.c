#include <stdlib.h>
#include "dog.h"

/**
 * _strlen - Calcule la longueur d'une chaîne de caractères
 * @s: La chaîne à mesurer
 *
 * Return: La longueur de la chaîne
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strcpy - Copie une chaîne de caractères dans un buffer
 * @dest: Destination
 * @src: Source
 *
 * Return: Pointeur vers dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * new_dog - Crée une nouvelle structure dog_t
 * @name: Nom du chien
 * @age: Âge du chien
 * @owner: Propriétaire du chien
 *
 * Return: Pointeur vers le nouveau dog_t, ou NULL en cas d'échec
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;
	int len_name, len_owner;

	if (name == NULL || owner == NULL)
		return (NULL);

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	len_name = _strlen(name);
	dog->name = malloc(sizeof(char) * (len_name + 1));
	if (dog->name == NULL)
	{
		free(dog);
		return (NULL);
	}

	len_owner = _strlen(owner);
	dog->owner = malloc(sizeof(char) * (len_owner + 1));
	if (dog->owner == NULL)
	{
		free(dog->name);
		free(dog);
		return (NULL);
	}

	_strcpy(dog->name, name);
	dog->age = age;
	_strcpy(dog->owner, owner);

	return (dog);
}
