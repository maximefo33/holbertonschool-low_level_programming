#include "main.h"
#include <stdlib.h>

/**
 * alloc_grid - Alloue une grille d'entiers à deux dimensions.
 * @width: Largeur de la grille (colonnes).
 * @height: Hauteur de la grille (lignes).
 *
 * Return: Un pointeur vers la grille allouée, ou NULL en cas d'échec.
 */
int **alloc_grid(int width, int height)
{
	int **grid;
	int i, j;

	if (width <= 0 || height <= 0)
		return (NULL);

	/* Allocation du tableau de pointeurs pour les lignes */
	grid = malloc(sizeof(int *) * height);
	if (grid == NULL)
		return (NULL);

	/* Allocation de chaque ligne */
	for (i = 0; i < height; i++)
	{
		grid[i] = malloc(sizeof(int) * width);
		if (grid[i] == NULL)
		{
			/* En cas d'échec, on libère tout ce qui a été alloué avant */
			for (j = 0; j < i; j++)
				free(grid[j]);
			free(grid);
			return (NULL);
		}

		/* Initialisation de la ligne à 0 */
		for (j = 0; j < width; j++)
			grid[i][j] = 0;
	}

	return (grid);
}
