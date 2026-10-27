/**
 * main - Point d'entrée du programme
 *
 * Description: Affiche l'alphabet en minuscules suivi d'un retour à la ligne
 * Return: Toujours 0 (Succès)
 */
#include <stdio.h>

int main(void)
{
	char lettre = 'a';

	while (lettre <= 'z')
	{
		if (lettre != 'e' && lettre != 'q')
		{
			putchar(lettre);
		}
		lettre++;
	}
	putchar('\n');
	return (0);
}
