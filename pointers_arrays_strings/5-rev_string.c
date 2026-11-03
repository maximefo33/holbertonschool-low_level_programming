#include "main.h"

/**
 * rev_string - Reverses a string in place.
 * @s: Pointer to the string to be reversed.
 *
 * Return: Nothing.
 */
void rev_string(char *s)
{
    int len = 0;
    int i = 0;
    char temp;

    /* 1. On calcule la longueur de la chaîne */
    while (s[len] != '\0')
    {
        len++;
    }

    /* 2. On échange les caractères du début et de la fin jusqu'au milieu */
    for (i = 0; i < len / 2; i++)
    {
        temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
    }
}
