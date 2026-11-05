/*
** REVERSE ARRAY : L'art du Kung-Fu appliqué aux pointeurs.
**
** On place un combattant 'a' au début et un combattant 'fin' tout au bout.
** Tant qu'ils ne se croisent pas au milieu (a < fin), ils s'échangent leurs
** valeurs en utilisant une chaise musicale 'temp' pour ne rien casser.
** À chaque round, 'a' avance, 'fin' recule, jusqu'au headbutt final au centre.
*/
void reverse_array(int *a, int n)
{
	int *fin = a + n - 1;
	int temp;

	while (a < fin)
	{
		temp = *a;
		*a = *fin;
		*fin = temp;

		a++;
		fin--;
	}
}