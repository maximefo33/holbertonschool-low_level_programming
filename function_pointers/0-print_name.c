/**
 * print_name - executes a function to print a name
 * @name: the name to be printed
 * @f: pointer to the function used to print the name
 *
 * Return: Nothing.
 */

void print_name(char *name, void (*f)(char *))
{
	f(name);
}
