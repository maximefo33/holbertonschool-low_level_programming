Mesure	Naive	Single-pass
Exécution 1	0,782 s	0,000 s
Exécution 2	0,781 s	0,000 s
Exécution 3	0,775 s	0,000 s
Moyenne	0,7793 s	0,000 s

Looking at the code of the two algorithms, I could already guess that the first would be much more computationally expensive than the second.

Indeed, the first uses a nested loop: for each element of the array, it iterates through the previous elements again. This results in numerous repeated checks and considerably increases the number of operations.

Conversely, the second algorithm uses a single loop and iterates through each element of the array only once. It therefore performs far fewer operations.

At first glance, I thought the second would be faster, and the measurements I took confirmed this hypothesis: the first takes approximately 0.78 seconds, while the second's time is less than the accuracy displayed by the program.

I also observed that the two algorithms do not produce the same result, which shows that they do not perform exactly the same calculation despite their stated objective.