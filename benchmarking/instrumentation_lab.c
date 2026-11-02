#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

static unsigned int next_value(unsigned int *state)
{
	*state = (*state * 1103515245u) + 12345u;
	return *state;
}

static void build_dataset(void)
{
	unsigned int state;
	int i;

	state = SEED_VALUE;

	for (i = 0; i < DATASET_SIZE; i++)
		dataset[i] = (int)(next_value(&state) % 100000);
}

static void process_dataset(void)
{
	int i;
	int v;

	for (i = 0; i < DATASET_SIZE; i++)
	{
		v = dataset[i];
		v = (v * 3) + (v / 7) - (v % 11);
		if (v < 0)
			v = -v;
		dataset[i] = v;
	}
}

static unsigned long reduce_checksum(void)
{
	unsigned long sum;
	int i;

	sum = 0;
	for (i = 0; i < DATASET_SIZE; i++)
		sum = (sum * 131ul) + (unsigned long)dataset[i];

	return sum;
}

int main(void)
{
	unsigned long checksum;

	/* Students must add clock-based timing and print required lines. */

	clock_t start;
	clock_t end;
	double elapsed_a;
	double elapsed_b;
	double elapsed_c;
	clock_t total_start;
	clock_t total_end;
	double total_global;
	total_start = clock();

	start = clock();
	build_dataset();
	end = clock();
	elapsed_a = (double)(end - start) / (double)CLOCKS_PER_SEC;

	start = clock();
	process_dataset();
	end = clock();
	elapsed_b = (double)(end - start) / (double)CLOCKS_PER_SEC;

	start = clock();
	checksum = reduce_checksum();
	end = clock();
	elapsed_c = (double)(end - start) / (double)CLOCKS_PER_SEC;

	total_end = clock();
	total_global = total_end - total_start;

	printf("TOTAL seconds:%.6f \n", (double)(total_global) / CLOCKS_PER_SEC);
	printf("BUILD_DATA seconds:%.6f \n", (double)(elapsed_a));
	printf("PROCESS seconds:%.6f\n", (double)(elapsed_b));
	printf("REDUCE seconds:%.6f\n", (double)(elapsed_c));
	/* Required output (exact format, no extra lines):
	 * TOTAL seconds: <float>
	 * BUILD_DATA seconds: <float>
	 * PROCESS seconds: <float>
	 * REDUCE seconds: <float>
	 */

	return 0;
}
