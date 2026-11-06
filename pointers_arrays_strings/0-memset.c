
/**
 * _memset - Fills the first n bytes of memory with a constant byte.
 * @s: Pointer to the memory area to modify.
 * @b: Constant byte to write.
 * @n: Number of bytes to fill.
 *
 * Return: A pointer to the memory area s.
 */

char *_memset(char *s, char b, unsigned int n)
{

	char *result = s;
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		*s = b;
		s++;
	}
	return (result);
}