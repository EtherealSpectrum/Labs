//ON. A.M.

#include <stdio.h>      // Standard input/output functions (printf, scanf, fgets, etc.)
#include <math.h>       // Mathematical functions (abs, etc.)
#include <stdbool.h>    // Boolean type support (bool, true, false)
#include <stdlib.h>     // Standard library functions (EXIT_SUCCESS)

// Function declarations (prototypes)
void userInitialization(int[], size_t); // Function to initialize array with user input

void section();  // Function to print section separators

bool decreasingOrder(int[], size_t);  // Checks if array is in decreasing order

bool increasingOrder(int[], size_t);  // Checks if array is in increasing order

int is_sorted(int*, int);

void printArray(int[], size_t);  // Prints all elements of the array

void printOrder(int[], size_t);  // Prints the order type of the array

int getMin(int[], size_t);  // Finds the minimum value in the array

int getMax(int[], size_t);  // Finds the maximum value in the array

unsigned int getMaxAbsolute(int[], size_t); // Finds the maximum absolute value in the array

size_t occurences_by_abs_value(int arr[], size_t length);

size_t occurrences(int[], size_t, int); // Counts occurrences of a specific value in the array

void trackSpots(int[], size_t, unsigned int, size_t[]); // Records positions where max absolute value occurs

void printSpots(size_t[], size_t); // Prints the positions stored in the spots array

int main() {
	const size_t LENGTH = 20;  // Constant defining array size (10 elements)
	int arr[LENGTH];  // Declare an integer array of size LENGTH

	userInitialization(arr, LENGTH); // Call function to fill array with user input

	section();  // Print section separator
	printArray(arr, LENGTH);  // Display all array elements

	section();  // Print section separator
	printOrder(arr, LENGTH); // Display whether array is increasing, decreasing, or chaotic

	int order = is_sorted(arr, LENGTH);
	printf("Order = %i", order);

	section();  // Print section separator
	unsigned max_abs_val = getMaxAbsolute(arr, LENGTH); // Find maximum absolute value in array
	printf("Greater absolute value is: %u\n", max_abs_val); // Print the maximum absolute value

	// Calculate total occurrences of both positive and negative versions of max absolute value
	size_t total = occurrences(arr, LENGTH, -max_abs_val)
			+ occurrences(arr, LENGTH, max_abs_val);
	size_t spots[total]; // Create array to store positions where max absolute value occurs

	trackSpots(arr, LENGTH, max_abs_val, spots); // Fill spots array with positions
	printf("Spots: ");
	for (size_t i = 0; i < total; i++)
		printf("%zu ", spots[i]);

	size_t how_many_times_occurs_max_element = occurences_by_abs_value(arr,
			LENGTH);
	printf("It occurs: %zu", how_many_times_occurs_max_element);

	section();  // Print section separator
	printSpots(spots, total); // Display the positions where max absolute value occurs

	return EXIT_SUCCESS;  // Return success status to operating system
}

// Function to initialize array with user input
void userInitialization(int arr[], size_t length) {
	printf("Enter %zu integers.\n", length); // Prompt user for required number of integers
	printf("\n");  // Print empty line for formatting

	char input[100]; // Buffer to hold user input as a string (max 99 characters + null terminator)
	for (size_t i = 0; i < length; i++) {  // Loop through each array position
		printf("arr[%zu] = ", i);  // Prompt for current array element
		// Keep reading input until the user enters a valid integer
		while (fgets(input, sizeof(input), stdin)) // Read a line of input from standard input
			// Try to read an integer from the input string
			if (sscanf(input, "%d", &arr[i]) == 1) // If successfully read one integer
				break; // Success: break out of the while loop
			else
				printf("arr[%zu] is invalid. Try again: ", i); // If not an integer, ask again
	}
}

// Function to print section separators
inline void section() {
	printf("\n\n");  // Print two newlines to create visual separation
}

// Function to check if array is in decreasing order
bool decreasingOrder(int arr[], size_t length) {
	for (size_t i = 0; i + 1 < length; i++) // Loop through array until second-to-last element
		if (arr[i] < arr[i + 1]) // If current element is less than next element
			return false;  // Array is not in decreasing order
	return true;  // All elements passed the test, array is in decreasing order
}

// Function to check if array is in increasing order
bool increasingOrder(int arr[], size_t length) {
	for (size_t i = 0; i + 1 < length; i++) // Loop through array until second-to-last element
		if (arr[i] > arr[i + 1]) // If current element is greater than next element
			return false;  // Array is not in increasing order
	return true;  // All elements passed the test, array is in increasing order
}

// Function to print all elements of the array
void printArray(int arr[], size_t length) {
	printf("Elements: ");  // Print label before displaying elements
	for (size_t i = 0; i < length; i++)  // Loop through each element
		printf("%d ", arr[i]);  // Print current element followed by space
}

// Function to record positions where maximum absolute value occurs in the array
void trackSpots(int arr[], size_t length, unsigned int max_abs_val,
		size_t spots[]) {
	// Loop through array with two counters: i for original array, j for spots array
	for (size_t i = 0, j = 0; i < length; i++)
		if (abs(arr[i]) == max_abs_val) // If current element's absolute value equals max absolute value
			spots[j++] = i; // Store current position in spots array and increment j
}

// Function to print the positions stored in the spots array
void printSpots(size_t arr[], size_t length) {
	// Use ternary operator to print "Spot" (singular) or "Spots" (plural) based on count
	printf("Spot%c: ", length == 1 ? '\0' : 's');
	for (size_t i = 0; i < length; i++) // Loop through each position in spots array
		printf("%zu ", arr[i]);  // Print the stored position
}

// Function to determine and print the order type of the array
void printOrder(int arr[], size_t length) {
	const char str[] = "order.";  // Common suffix string for order messages
	if (decreasingOrder(arr, length))  // Check if array is in decreasing order
		printf("Decreasing %s\n", str);  // Print decreasing order message

	else if (increasingOrder(arr, length)) // Check if array is in increasing order
		printf("Increasing %s\n", str);  // Print increasing order message

	else
		printf("Chaos\n"); // Print chaos message if neither increasing nor decreasing
}
int is_sorted(int *A, int N) {
	if (decreasingOrder(A, N))  // Check if array is in decreasing order
		return -1;  // Print decreasing order message

	else if (increasingOrder(A, N)) // Check if array is in increasing order
		return 1;  // Print increasing order message

	else
		return 0; // Print chaos message if neither increasing nor decreasing
}
// Function to find the minimum value in the array
int getMin(int arr[], size_t length) {
	int min = arr[0];  // Assume first element is the minimum

	for (size_t i = 1; i < length; i++)  // Loop through remaining elements
		if (arr[i] < min)  // If current element is smaller than current minimum
			min = arr[i];  // Update minimum value

	return min;  // Return the smallest value found
}

// Function to find the maximum value in the array
int getMax(int arr[], size_t length) {
	int max = arr[0];  // Assume first element is the maximum

	for (size_t i = 1; i < length; i++)  // Loop through remaining elements
		if (arr[i] > max)  // If current element is larger than current maximum
			max = arr[i];  // Update maximum value

	return max;  // Return the largest value found
}

// Function to find the maximum absolute value in the array
unsigned int getMaxAbsolute(int arr[], size_t length) {
	unsigned int min = abs(getMin(arr, length)); // Get absolute value of minimum element
	unsigned int max = abs(getMax(arr, length)); // Get absolute value of maximum element

	if (max > min)  // Compare which absolute value is larger
		return max;  // Return maximum absolute value

	return min; // Return minimum absolute value (if they're equal or min is larger)
}

size_t occurences_by_abs_value(int arr[], size_t length) {
	unsigned int max_abs_val = getMaxAbsolute(arr, length);
	return occurrences(arr, length, max_abs_val)
			+ occurrences(arr, length, -max_abs_val);
}

// Function to count how many times a specific value appears in the array
size_t occurrences(int arr[], size_t length, int search) {
	size_t occurs = 0;  // Counter for occurrences

	for (size_t i = 0; i < length; i++)  // Loop through all elements
		if (search == arr[i])  // If current element matches search value
			occurs++;  // Increment occurrence counter

	return occurs;  // Return total count of occurrences
}

