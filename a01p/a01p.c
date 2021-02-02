// do not change this code except in the following ways:
//   * write code for the following functions:
//      * bigOrSmallEndian()
//      * getNextHexInt()
//      * printNumberData()
//   * change studentName by changing "I. Forgot" to your actual name

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static char *studentName = "Chris Hall";

// report whether machine is big or small endian
void bigOrSmallEndian()
{
	unsigned int i = 1;
	char* ptr = (char*) & i;

	if (*ptr == 1) {    // First a 1?
		printf("Byte order: little-endian.\n\n");
	}
	else {
		printf("Byte order: big-endian.\n\n");
	}
}

// get next int (entered in hex) using scanf()
// returns true (success) or false (failure)
// if call succeeded, return int value via iPtr
bool getNextHexInt(unsigned int *iPtr)
{
    *iPtr = 0;

    if (scanf("%X", iPtr) == 1) {
        return true;
    }
    else {
        return false;
    }
}

// print requested data for the given number
void printNumberData(int i)
{
    int signBit = 0;
    int exponentBits = 0;
    int fractionalBits = 0;

    exponentBits = i & 0x7f800000;
    exponentBits = exponentBits >> 23;  // Shift right
    fractionalBits = i & 0x007FFFFF;

    if ((i & 0x80000000) == 0x80000000) {
        signBit = 1;
        printf("signBit 1");
    }
    else {
        signBit = 0;
        printf("signBit 0");     
    }

    printf(", expBits %3d, fractBits 0x%08X\n", exponentBits, fractionalBits);

    if (exponentBits == 0) {
        if (fractionalBits != 0) {
            printf("denormalized: exp = %d", (exponentBits - 126));
        }
        else {
            if (signBit == 0) {
                printf("+zero");
            }
            else {
                printf("-zero");
            }
        }

    }

    else {
        if (exponentBits == 0xFF) {
            if (fractionalBits == 0) {
                printf("+infinity");
            }
            else if (fractionalBits == 1) {
                printf("-infinity");
            }
            else {
                printf("%cNaN", fractionalBits < 0X400000 ? 'S' : 'Q');
            }
        }
        if (exponentBits != 0 && exponentBits != 0xff) {
            printf("normalized:   exp = %d", (exponentBits - 127));
        }
    }

    printf("\n\n");
}

// do not change this function in any way
int main(int argc, char **argv)
{
	unsigned int	i;					// number currently being analyzed
	bool			validInput;			// was user input valid?

	printf("CS201 - A01p - %s\n\n", studentName);
	bigOrSmallEndian();
	for (;;) {
		if (argc == 1)						// allow grading script to control ...
			printf("> ");					// ... whether prompt character is printed
		validInput = getNextHexInt(&i);
		printf("0x%08X\n", i);
		if (! validInput) {					// encountered bad input
			printf("bad input\n");
			while (getchar() != '\n') ;		// flush bad line from input buffer
			continue;
			}
		printNumberData(i);
		if (i == 0) {
			printf("bye...\n");
			break;
			}
		}
	printf("\n");
	return 0;
}