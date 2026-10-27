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
	char lettre2 = 'A';

	while (lettre <= 'z')
	{
		putchar(lettre);
		lettre++;
	}
	while (lettre2 <= 'Z')
	{

		putchar(lettre2);

		lettre2++;
	}
	putchar('\n');
	return (0);
}
