#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point of the simple calculator program.
 *
 * Description: Displays an interactive menu and allows the user
 * to choose an arithmetic operation or quit the program.
 *
 * Return: Always 0 (Success).
 */

void addition(void)
{
	int a = 0;
	int b = 0;
	int resultat;
	printf("Saisissez le premier chiffre a additionner:\n ");
	scanf("%d", &a);
	printf("Saisissez le deuxième  chiffre a additionner:\n ");
	scanf("%d", &b);
	resultat = a + b;
	printf("Result:%d\n", resultat);
}

int main(void)
{
	int chois = 0;

	do

	{
		printf("Simple Calculator\n ");
		printf("1) Add\n 2) Subtract\n 3) Multiply\n 4) Divide\n 0) Quit\n");
		printf("Choice: : ");
		scanf("%d", &chois);
		if (chois == 0)
		{
			printf("Bye!\n");
		}

		else if (chois == 1)
		{

			addition();
		}

		else
		{
			printf("Invalid choice");
		}

	} while (chois != 0);
	return 0;
}
