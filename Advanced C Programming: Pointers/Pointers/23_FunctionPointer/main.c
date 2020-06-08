#include <stdio.h>

typedef int(*PFI) (int);

int square(int a) {
	return a * a;
}


int main(int argc, char **argv) {
	//  int (*test)();
	// double(*test)(double);
	// int (*test)(int);

    PFI test;
	test = square;

	printf("Result=%d\n", test(4));
	return 0;
}
