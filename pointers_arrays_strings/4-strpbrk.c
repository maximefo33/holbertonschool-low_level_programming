
/**
 * _strpbrk - Searches a string for any of a set of bytes.
 * @s: The string to search.
 * @accept: The bytes to look for.
 *
 * Return: A pointer to the byte in s that matches one of the bytes in accept,
 *         or NULL if no such byte is found.
 */

char *_strpbrk(char *s, char *accept)
{
	char *reset_accept = accept;

	while (*s != '\0')
	{
		accept = reset_accept;

		while (*accept != '\0')
		{
			if (*s == *accept)
			{
				return (s);
			}
			accept++;
		}

		s++;
	}

	return (0);
}
