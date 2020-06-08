#include <stdio.h>

int main(int argc, char **argv) {
	int num;
    int num2;
    num = 100;

    // A pointer variable is declared (of type int == can point to addresses of int type):
	int *numPtr;

    // To obtain the address of the variable num and give it to the pointer numPtr
	numPtr = &num;

    // Indirection or deferencing == getting the value at the address pointed by numPtr
	num2 = *numPtr;

	printf("num=%d, numPtr=%d, address of num=%d, num2=%d\n", num, numPtr, &num, num2);
	printf("%p - %p ; %d - %d\n", numPtr, numPtr+5, numPtr, numPtr + 5);
	return 0;
}
