#include <stdio.h>

int main(void)
{
	char lettre = 'a';

	while (lettre <= 'z')
	{
		putchar(lettre);
		lettre++;
	}
	putchar('\n');
	return (0);
}
