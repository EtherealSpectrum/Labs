// ΚΑΚΟΥΛΛΗΣ XXXXXXXXXXXXX Παρασκευής 15:00–17:00 (Τμήμα 6).

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int digitSum(int);

unsigned int* digital_root(int n);

//unsigned int digitalRoot(int);

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

int main() {
	printf("Give the size of the list: ");

	int sizeList;
	while (true) { // @suppress("Symbol is not resolved")

		scanf("%d", &sizeList);

		if (sizeList > 0)
			break;

		printf("Invalid number.\n");
		printf("Error Message: Non positive number.\n");
		printf("Please, try again to enter a positive number: ");

	}

	printf("\n");

	for (int i = 0; i < sizeList; i++) {
		printf("Enter an integer number: "); //Inform the user.

		int number;
		while (true) { // @suppress("Symbol is not resolved")
			scanf("%d", &number);

			if (number != 0)
				break;

			//Error messages.
			printf("Invalid number.\n");
			printf("Error Message: Non zero number.\n");
			printf("Please, try again to enter a integer number: ");
		}

		printf("\n");

		int *dgr = digital_root(number);
		printf("The digital root of the number %d is: %u\n\n", number, *dgr);

		size_t length = 1;
		unsigned int absolute = abs(number);
		while (*dgr != absolute) {
			dgr--;
			length++;
		}

		printf("Digit Sums: ");

		unsigned int sums[length];
		unsigned int sum = 0;
		for (size_t i = 0; i < length; i++, dgr++) {
			sums[i] = *dgr;
			printf("%d ", *dgr);
		}

		printf("\n\n");

		if (sums[length - 1] == 5)
			if (isPrime(number))
				printf("Number %d is prime.", number);
			else
				printf("Number %d is not prime.", number);

		printf("\n\n\n\n");
	}
}

unsigned int digitSum(int n) {
	n = abs(n);

	unsigned int sum = 0;
	while (n > 0) {
		sum += n % 10; // grab the last digit of n and add it in the sum.
		n /= 10; // delete the last digit of the n.
	}

	return sum;
}

unsigned int* digital_root(int n) {
	size_t qt = 1;
	int *dgr_step = (int*) malloc(qt * sizeof(int));
	dgr_step[0] = abs(n);
	for (int i = 0; dgr_step[i] > 9; i++) {
		qt++;
		dgr_step = (int*) realloc(dgr_step, qt * sizeof(int));
		dgr_step[i + 1] = digitSum(dgr_step[i]);
	}

	return &dgr_step[qt - 1];
}

