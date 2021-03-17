// Numbers from command line arguments are sent to child process
// from parent process one at a time through pipe.
//
// Child process adds up numbers sent through pipe.
//
// Child process returns sum of numbers to parent process.
//
// Parent process prints sum of numbers.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>

int main(int argc, char** argv) {
	static int fd[2];
	int num = argc;	// revision here

	// set up pipe
	pid_t pid;

	if (pipe(fd)) {							// error check
		printf("Pipe error\n");
		return -1;
	}

	// call fork()
	pid = fork();

	if (pid < 0) {							// error check
		printf("Fork error %d\n", pid);
		return -1;
	}

	if (pid == 0) {
		// -- running in child process --
		double sum = 0;		
		double argIn = 0;
		int ret;

		close(fd[1]);	// revision here

		// Receive numbers (doubles) from parent process via pipe
		// one at a time, and add them up.
		for (int i = 1; i < num ; i++) {		// revision here (removed argc)
			read(fd[0], &argIn, sizeof(sum));
			sum = sum + argIn;
		}
		
		// Return sum of numbers, converted to int.
		ret = sum;
		return ret;
	}
	else {
		// -- running in parent process --
		int sum = 0;
		double argOut;

		close(fd[0]);	// revision here

		// Send numbers (datatype: double, 8 bytes) from command line arguments
		// starting with argv[1] one at a time through pipe to child process.
		for (int i = 1; i < argc; i++) {
			argOut = atof(argv[i]);
			write(fd[1], &argOut, sizeof(argOut));
		}
	
		printf("CS201 - Assignment 3 Regular - Chris Hall\n");		// second submission
		// Wait for child process to return. Reap child process.
		// Receive sum of numbers (as an int) via the value returned when
		// the child process is reaped.
		
		close(fd[1]);	// revision here

		if (waitpid(pid, &sum, 0)) {
			if (WIFEXITED(sum))
				printf("sum = %d\n", WEXITSTATUS(sum));
		}

		return 0;
	}
}