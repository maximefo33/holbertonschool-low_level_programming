/**
 * reverse_array - Reverses the content of an array of integers.
 * @a: Pointer to the array of integers.
 * @n: Number of elements in the array.
 *
 * Return: Nothing.
 */
void reverse_array(int *a, int n)
{
	int *fin = a + n - 1;
	int temp;

	while (a < fin)
	{
		temp = *a;
		*a = *fin;
		*fin = temp;

		a++;
		fin--;
	}
}
