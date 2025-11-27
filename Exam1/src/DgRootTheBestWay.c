/*
 ============================================================================
 Name        : DgRoot.c
 Author      : Nikitas K.
 Created on	 : 27 Νοε 2025
 Version	 :
 Copyright   : MIT License
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int filterInput();

size_t getReductionSteps(int);

unsigned int digitalRoot(int, int[]);

unsigned int digitSum(int);

void printArray(int[], int);

bool isPrime(int); // @suppress("Type cannot be resolved")

int main() {
	int sizeList;

	printf("Give the size of the list: ");
	while (true) { // @suppress("Symbol is not resolved")
		sizeList = filterInput();
		if (sizeList > 0)
			break;

		printf("Invalid size list.\n");
		if (sizeList == 0)
			printf("Error Message: Neutral number.\n");
		if (sizeList < 0)
			printf("Error Message: Negative number.\n");

		printf("Please, try again to enter a positive integer: ");
	}
	for (size_t i = 1; i <= sizeList; i++) {
		printf("\n\nState: %zu\n", i);
		printf("Enter an integer number: ");
		int in;
		while (true) { // @suppress("Symbol is not resolved")
			in = filterInput();
			if (in != 0)
				break;

			printf("Invalid number.\n");
			printf("Error Message: Neutral number.\n");

			printf("Please, try again to enter a non zero integer: ");
		}

		size_t length = getReductionSteps(in);
		int sums[length];
		unsigned int dgroot = digitalRoot(in, sums);

		printf("The digital root of the number %d is: %u", in, dgroot); // Also it initializes the array.

		if (length > 0) {
			printf("\n");
			printArray(sums, length);
		}

		if (dgroot == 5) {
			printf("\nNumber ");

			if (isPrime(in))
				printf("%d is prime.", in);
			else
				printf("%d is not prime.", in);
		}

	}

	printf("\n\n\nThe list has finished.");
}

int filterInput() {

	int number;
	char input[100];

	while (fgets(input, sizeof(input), stdin))
		if (sscanf(input, "%d", &number) == 1)
			break;
		else {
			printf("Invalid input.\n");
			printf("Error Message: Not a number.\n");
			printf("Please, try again to enter an integer number: ");
		}

	return number;
}

size_t getReductionSteps(int n) {
	if (n < 0)
		n = -n;

	int length = 0;
	while (n > 9) {
		length++;
		n = digitSum(n);
	}

	return length;
}

unsigned int digitalRoot(int n, int arr[]) {
	if (n < 0)
		n = -n;

	size_t i = 0;
	while (n > 9) {
		arr[i] = digitSum(n);
		n = arr[i];
		i++;
	}

	return n;
}

unsigned int digitSum(int n) {
	if (n < 0)
		n = -n;

	unsigned int sum = 0;
	while (n > 0) {
		sum += n % 10;
		n /= 10;
	}

	return sum;
}

void printArray(int arr[], int length) {
	printf("Elements: ");
	for (size_t i = 0; i < length; i++)
		printf("%d ", arr[i]);
}

bool isPrime(int n) { // @suppress("Type cannot be resolved")
	if (n < 0)
		n = -n;

	if (n <= 1)
		return false; // @suppress("Symbol is not resolved")

	if (n <= 3) // 2, 3 are can't be written in the form of: 6k - 1 or 6k + 1
		return true; // @suppress("Symbol is not resolved")

	/*
	 * For all integers x it exists an integer k and it exists a number c member of the set {-1, 0, 1, 2, 3, 4} such that (x = 6k-c).
	 * For all primes x it exists an integer k such that (x = 6k - 1 or x = 6k + 1).
	 */

// This is checked so that we can skip
// middle five numbers in below loop
	if (n % 2 == 0 || n % 3 == 0)
		return false; // @suppress("Symbol is not resolved")

//Now we know n is not equal with any of these numbers 6k, 6k+2, 6k+3, 6k+4, therefore
	for (int i = 5; i * i <= n; i += 6)
		if (n % i == 0 || n % (i + 2) == 0) // if(6k - 1 | n or 6k + 1 | n) then return false.
			return false; // @suppress("Symbol is not resolved")

	return true; // @suppress("Symbol is not resolved")
}
