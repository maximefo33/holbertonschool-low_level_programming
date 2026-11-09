#include "main.h"
#include <stdlib.h>

/**
 * free_grid - Libère une grille à deux dimensions précédemment créée.
 * @grid: Pointeur vers la grille à deux dimensions.
 * @height: Hauteur de la grille (nombre de lignes).
 *
 * Return: void.
 */
void free_grid(int **grid, int height)
{
    int i;

    if (grid == NULL || height <= 0)
        return;

    /* On libère chaque ligne une par une */
    for (i = 0; i < height; i++)
    {
        free(grid[i]);
    }

    /* On libère le tableau de pointeurs principal */
    free(grid);
}
