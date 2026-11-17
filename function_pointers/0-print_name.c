void print_name(char *name, void (*f)(char *))
{
	/**
	 * print_name - prints a name using a given function
	 * @name: name to be passed to the function
	 * @f: pointer to the function that prints the name
	 *
	 * Return: Nothing.
	 */

	/* f est le pointeur vers la fonction.
	 * name contient la chaîne à transmettre à cette fonction.
	 */
	f(name);
}