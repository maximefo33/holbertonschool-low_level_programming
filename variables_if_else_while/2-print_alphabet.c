#include <stdio.h>

int main(void)
{
    char lettre = 'a';

    while (lettre <= 'z')
    {
        putchar(lettre);
        lettre++;
    }
    // ... ton while et ton deuxième putchar ...
    putchar('\n');
    return (0);
}