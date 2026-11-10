#include <stdlib.h>

/**
 * array_range - Crée un tableau d'entiers contenant une plage de valeurs.
 * @min: La valeur minimale (incluse).
 * @max: La valeur maximale (incluse).
 *
 * Return: Un pointeur vers le tableau nouvellement créé.
 *         NULL si min > max ou si l'allocation malloc échoue.
 */
int *array_range(int min, int max)
{
	int *array;
	int size, i;

	/* Étape 1 : Vérifier si la condition de validité est respectée */
	if (min > max)
		return (NULL);

	/* Étape 2 : Calculer la taille nécessaire pour le tableau */
	size = max - min + 1;

	/* Étape 3 : Allouer la mémoire avec malloc */
	array = malloc(sizeof(int) * size);
	if (array == NULL)
		return (NULL);

	/* Étape 4 : Remplir le tableau de min à max */
	for (i = 0; i < size; i++)
	{
		array[i] = min + i;
	}

	/* Étape 5 : Retourner le pointeur du tableau */
	return (array);
}
