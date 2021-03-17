#include <stdio.h>
#include <stdlib.h>

// You are only allowed to make changes to this code as specified by the comments in it.

// The code you submit must have these two values.
#define N_TIMES		600000
#define ARRAY_SIZE	 10000

int main(void) 
{
	double	*array = calloc(ARRAY_SIZE, sizeof(double));
	double	sum = 0;
	int		i;

	// You can add variables between this comment ...
	double a = 0, b = 0;
	// ... and this one.

	// Please change 'your name' to your actual name.
	printf("CS201 - Asgmt 4 - Chris Hall\n");

	for (i = 0; i < N_TIMES; i++) {

		// You can change anything between this comment ...
		double* j;

		for (j = array; j < &array[ARRAY_SIZE]; j += 14) {
			a += (*j) + *(j + 1) + *(j + 2) + *(j + 3) + *(j + 4) + *(j + 5) + *(j + 6);
			b += *(j + 7) + *(j + 8) + *(j + 9) + *(j + 10) + *(j + 11) + *(j + 12) + *(j + 13);
		}
		// ... and this one. But your inner loop must do the same
		// number of additions as this one does.
	}
	// You can add some final code between this comment ...
	sum += a + b;
	// ... and this one.

	return 0;
}