## Observed Performance Differences

Based on the two executions, all four measurements returned the same displayed value: 0.000000 seconds. This includes the total execution time and the individual execution times of `BUILD_DATA`, `PROCESS`, and `REDUCE`.

Based on these results, there is no visible performance difference between the three functions. However, this does not necessarily mean that they have no performance issues. The measured times are displayed as 0.000000 seconds, which means that the measurement precision is not sufficient to show any differences.

In this situation, I believe it is more important to check whether each function produces the expected output rather than focusing only on how quickly it executes. The correctness of the results is essential when evaluating whether the process is working as expected.

## Relation Between Runtime and Energy Consumption

Based on the available measurements, I cannot determine whether my program consumed a large or a small amount of energy.

The recorded execution times are displayed as 0.000000 seconds, but I did not collect any direct measurements of electrical power or energy consumption.

Therefore, I do not have enough information to establish an accurate relationship between runtime and energy consumption. Additional measurements would be necessary to evaluate the program's actual energy usage.

## Limitations of the Experiment

One limitation of my experiment is that the collected measurements do not show whether each function produces the expected result.

For example, if I wanted to count the number of cards in a deck, one function could return the correct number while another could execute faster but return an incorrect result.

If I only compared execution times, I might choose the faster function without checking whether it actually works correctly.

Therefore, performance measurements alone are not enough to evaluate a function. It is also necessary to verify the correctness of its output before deciding whether it is suitable.

## Practical Engineering Takeaway

Based on this experiment, I would recommend that developers follow the required coding standards and recommendations, such as the Betty style guidelines used at Holberton School.

I would also recommend avoiding unnecessary operations and queries in the code and performing all the necessary tests to check both performance and functionality.

Finally, code should be clean, readable, and well organized. This makes it easier to understand, maintain, and improve over time.

A good developer should not focus only on execution speed. The code must also produce the expected results and remain easy to maintain.

## Measurement Methodology

To obtain my measurements, I used the `clock()` function from the `time.h` library.

I developed my script based on Exercise 1. I reviewed the work I had completed in Exercise 1 and realized that I could reuse and adapt the same approach in my file for Exercise 2.

After developing my script, I was able to measure the execution times of the different functions and collect the results presented in this report.

Function / Measurement	Execution 1 (seconds)	Execution 2 (seconds)
TOTAL	0.000000	0.000000
BUILD_DATA	0.000000	0.000000
PROCESS	0.000000	0.000000
REDUCE	0.000000	0.000000