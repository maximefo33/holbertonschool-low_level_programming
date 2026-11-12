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

int main(void)
{
	int chois = 0;

	do

	{
		printf("Simple Calculator\n ");
		printf("1) Add\n 2) Subtract\n 3) Multiply\n 4) Divide\n 0) Quit\n");
		printf("Choice: : ");
		if (scanf("%d", &chois) == 1)
		{
			printf("Bye!");
		}
	} while (chois != 0);
	return 0;
}
