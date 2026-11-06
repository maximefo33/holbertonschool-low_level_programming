
/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @s: Pointer to the string to search.
 * @c: Character to locate.
 *
 * Return: A pointer to the first occurrence of c, or NULL if not found.
 */

char *_strchr(char *s, char c)
{
	while (*s != c && *s != '\0')
	{
		s++;
	}
	if (*s == '\0' && c != '\0')
	{
		return (NULL);
	}

	return (s);
}
