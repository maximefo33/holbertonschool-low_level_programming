#include <stdio.h>
#include <stdlib.h>
/**
 * main - Multiplies two numbers
 * @argc: Number of arguments, including the program name
 * @argv: Array containing the program name and arguments
 *
 * Return: 0 on success, 1 if the number of arguments is incorrect
 */
int main(int argc, char *argv[])
{
	int number1;
	int number2;
	int result;

	if (argc != 3)
	{
		printf("Error\n");
		return (1);
	}
	number1 = atoi(argv[1]);
	number2 = atoi(argv[2]);
	result = number1 * number2;
	printf("%d\n", result);

	return (0);
}
