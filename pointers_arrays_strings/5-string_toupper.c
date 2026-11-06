
/**
 * string_toupper - Changes all lowercase letters to uppercase.
 * @str: Pointer to the string to convert.
 *
 * Return: A pointer to the modified string.
 */

char *string_toupper(char *str)
{

	char *result = str;

	while (*str != '\0')
	{
		*str + 32;
		str++;
	}
	return (result);
}
