// ΚΑΚΟΥΛΛΗΣ XXXXXXXXXXXXX Παρασκευής 15:00–17:00 (Τμήμα 6).

#include <stdio.h>  // To be able to print and scan.
#include <stdlib.h> // To be able to have fancy and descriptive return statements.
#include <stdbool.h> //To be able to use boolean values. Like true 1, false 0.

//This function has one parameter the integer number n and it calculates his sum of digits.
unsigned int digitSum(int); //Declaration of the function.

unsigned int digital_root(int, unsigned int);

//This function calculates the digital root of a number using the digitSum function.
unsigned int digitalRoot(int); //Declaration of the function

bool is_single_digit(int); // @suppress("Type cannot be resolved")

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
	scanf("%d", &sizeList);

//	bool flag = true; // @suppress("Symbol is not resolved")

	for (int i = 0; i < sizeList; i++) {
		printf("Time: i = %d", i + 1);
		printf("\n\n");

		//Inform the user.
		printf("Enter an integer number: ");
		int number; // declare n
		while (true) { // @suppress("Symbol is not resolved")
			scanf("%d", &number); //initialize n
			if (number > 0 || number < 0) //if everything is satisfied we can move to the test part.
				break;
			//The above condition is not satisfied so the user entered a negative number.

			//Error messages.
			printf("Invalid number.\n");
			printf("Error Message: Non zero number.\n");

			//Inform the use to try again and this time to enter a positive number.
			printf("Please, try again to enter a integer number: ");
		}

		//Proof that the algorithm is working.
		// The %u is the best way to print an unsigned integer.

		int dgroot = digitalRoot(number);
		printf("\n");	// new line
		printf("The digital root of the number %d is: %d", number, dgroot);

		printf("\n\n");
		if (dgroot == 5)
			if (isPrime(number))
				printf("Number %d is prime", number);
			else
				printf("Number %d is not prime", number);

		printf("\n\n");
	}

}
//Implementation
unsigned int digitSum(int n) {
	if (n < 0) // if a number is negative make it positive.
		n = -n; // assign the opposite value to n, to make it positive.
	unsigned int sum = 0; // the initial sum of the digits is 0.
	while (n > 0) {
		sum += n % 10; // grab the last digit of n and add it in the sum.
		n /= 10; // delete the last digit of the n.
	}
	return sum; //return the sum
}

//Implementation
unsigned int digitalRoot(int n) {
	int store = n;
	if (n < 0)
		n = -n;

	//89798  ---> 41 ---> 5
	int length = 1;
	int dgroot = n;
	while (!is_single_digit(dgroot)) { //While n is not a single digit number do:
		dgroot = digitSum(dgroot); // assign the digit sum to this number.
		length++;
	}

	int arr[length];
	arr[0] = store;
	for (int i = 1; i < length; i++)
		arr[i] = digitSum(arr[i - 1]);

	//print
	printf("Elements of the array: ");
	for (int i = 0; i < length; i++)
		printf("%d ", arr[i]);

	printf("\n"); // new line

	int sumElements = 0;
	//sum all his elements.
	for (int i = 0; i < length; i++)
		sumElements += arr[i];

	printf("The sum of the elements is: %d\n", sumElements);
//	for (int i = 0; i < length; i++)
//		printf("%d ", arr[i]);

	return dgroot;
}

//inline unsigned int digital_root(int n, unsigned int base) {
//	if (n < 0)
//		n = -n;
//
//	return n - (base - 1) * ((n - 1) / (base - 1));
//}

bool is_single_digit(int number) { // @suppress("Type cannot be resolved")
	if (number < 0)
		number = -number;

	return 0 <= number && number <= 9;
}

