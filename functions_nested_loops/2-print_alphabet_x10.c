void print_alphabet_x10(void)
{
	char lettre;
	int i = 0; /* Ton compteur de lignes (de 0 à 9, ça fait 10 lignes) */

	while (i < 10) /* BOUCLE EXTERNE : Elle gère les 10 lignes */
	{
		lettre = 'a'; /* IMPORTANT : On remet la lettre à 'a' à chaque nouvelle ligne */

		while (lettre <= 'z') /* BOUCLE INTERNE : Elle gère l'alphabet en cours */
		{
			_putchar(lettre);
			lettre++;
		}

		_putchar('\n'); /* On change de ligne quand l'alphabet est fini */
		i++;		/* On passe à la ligne suivante */
	}
}
