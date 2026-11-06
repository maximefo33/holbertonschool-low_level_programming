
/**
 * _strspn - Counts matching characters at the start of a string.
 * @s: The string to check.
 * @accept: The characters to look for.
 *
 * Return: The number of matching characters.
 */

unsigned int _strspn(char *s, char *accept)
{
	char *a = accept;
	unsigned int counter = 0;
	int found;

	while (*s != '\0')
	{
		accept = a;
		found = 0;

		while (*accept != '\0')
		{
			if (*s == *accept)
			{
				found = 1;
				break;
			}
			accept++;
		}

		if (found == 0)
		{
			break;
		}

		counter++;
		s++;
	}

	return (counter);
}
