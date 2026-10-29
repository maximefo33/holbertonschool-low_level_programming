#include "main.h"

/**
 * jack_bauer - Prints every minute of the day
 *
 * Return: Nothing
 */
void jack_bauer(void)
{
	int heure;
	int minute;

	for (heure = 0; heure <= 23; heure++)
	{
		int unite = heure % 10;
		int dizaine = heure / 10;
		_putchar(dizaine + '0');
		_putchar(unite + '0');
		_putchar(':');

		for (minute = 0; minute <= 59; minute++)
		{

			int minut = minute / 10;
			int second = minute % 10;
			_putchar(minut + '0');
			_putchar(second + '0');
				}
		_putchar('\n');
	}
}