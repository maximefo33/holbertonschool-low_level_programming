#include <stdio.h>

/**
 * main - Prints all arguments passed to the program
 * @argc: Number of arguments, including the program name
 * @argv: Array containing the program name and arguments
 *
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}

	return (0);
}
