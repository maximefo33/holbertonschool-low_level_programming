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