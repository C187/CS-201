#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv) {

	printf("CS 201 - Assignment 2 - Chris Hall\n");

	int i, total = 0;
	double x, y, d, pi;

	// Set random number
	srand48(0);

	// Get the number inputed in the command line
	int inputNum = atoi(argv[1]);

	for (i = 0; i < inputNum; i++) {
		x = drand48();
		y = drand48();
		
		// I interpreted the instructions as doing all of pythagorean in asm. 
		// But it seems that I can't use fmulp since it wasn't shown in asm.c. 
		// So the three asm() blocks below commented out are to show the whole
		// process if fmulp was permitted.
		
		/*	
		// Square x
		asm("	fldl	%[xIn]	\n"
			"	fld		%%st	\n"
			"	fmulp			\n"
			"	fstpl	%[xOut]	\n"
			:	[xOut]	"=m"	(x)
			:	[xIn]	"m"		(x)
			:	"eax"
			);
	
		// Square y
		asm("   fldl    %[yIn]  \n"
		    "   fld		%%st    \n"
			"   fmulp           \n"
			"   fstpl   %[yOut] \n"
			:	[yOut]	"=m"    (y)
			:	[yIn]	"m"     (y)
			:	"eax"
		);
		
		// d^2 = x^2 + y^2
		asm("	fldl	%[xIn]	\n"
			"	fldl	%[yIn]	\n"
			"	faddp			\n"
			"	fstpl	%[dOut]	\n"
			:	[dOut]	"=m"	(d)
			:	[xIn]	"m"		(x),
				[yIn]	"m"		(y)
			:	"eax"
		);
		*/	

		// Below squares x and y the normal way then adds them in the asm block.
		// Comment out from here to before the if statement to uncomment and run
		// the commented out code above.

		double x2, y2;

		x2 = x * x;
		y2 = y * y;

		asm("	fldl	%[x2In]	\n"
			"	fldl	%[y2In]	\n"
			"	faddp			\n"		// x^2 + y^2
			"	fstpl	%[dOut]	\n"		// = d^2
			:	[dOut]	"=m"	(d)
			:	[x2In]	"m"		(x2),
				[y2In]	"m"		(y2)
			:	"eax"
		);
		
		if (d <= 1) total++;
	}

	// Find pi
	pi = (double)total / inputNum * 4;

	// Output
	printf("%i darts : pi = %.10f\n", inputNum, pi);

	return 0;
}
