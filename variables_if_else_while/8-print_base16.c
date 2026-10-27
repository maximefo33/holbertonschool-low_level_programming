#include <stdio.h>

/**
 * main - Point d'entrée du programme
 *
 * Description: Affiche tous les nombres de la base 16 en minuscules suivis d'un retour à la ligne
 * Return: Toujours 0 (Succès)
 */
int main(void)
{
	char lettre = 'a';
	char symbole = '0';

	/* On commence par afficher les chiffres de 0 à 9 */
	while (symbole <= '9')
	{
		putchar(symbole);
		symbole++;
	}

	/* Puis on enchaîne avec les lettres de a à f */
	while (lettre <= 'f')
	{
		putchar(lettre);
		lettre++;
	}

	putchar('\n');
	return (0);
}
