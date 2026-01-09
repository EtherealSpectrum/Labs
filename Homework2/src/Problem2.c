// KAKOULLIS 1117202500063

// Include standard input/output library for printf and getchar
#include <stdio.h>
// Include string library for strlen and strcpy functions
#include <string.h>
// Include standard library (not strictly needed in this code)
#include <stdlib.h>

// Function prototypes - declarations without implementation
void initialization(char[], size_t); // Function to initialize string from user input

void toLower(char[]);                 // Function to convert string to lowercase

int count_word(char text[], char word[]);

// Main function - program entry point
int main() {
	// Define maximum string length constant (50 characters + null terminator)
	const size_t LIMIT = 80;
	// Declare character array to store input string with space for null terminator
	char str[LIMIT + 1];

	// Prompt user for input
	printf("Give a string (max %zu characters): ", LIMIT);
	// Call initialization function to read user input
	initialization(str, sizeof(str));

	// Print the length of the input string using strlen function
	printf("Length: %zu\n", strlen(str));

	// Create another character array with same size as original string
	char lower[sizeof(str)];

	// Copy original string to 'lower' array using strcpy
	strcpy(lower, str);

	// Convert the copied string to lowercase
	toLower(lower);

	// Define the keyword we're searching for
	const char KEY[] = "hello";

	int spaces = 0;
	int puncts = 0;
	// Initialize counter for keyword occurrences
	size_t counter = 0;
	// Loop through the string, stopping 4 characters before the end
	for (int i = 0; i + 4 < strlen(lower); i++) {
		// Check if current position and next 4 characters match "hello"
		if (lower[i] == KEY[0] && lower[i + 1] == KEY[1]
				&& lower[i + 2] == KEY[2] && lower[i + 3] == KEY[3]
				&& lower[i + 4] == KEY[4])
			counter++;  // Increment counter if match found

		if (lower[i] == ' ')
			spaces++;

		//Or ascii table!
		if (str[i] == ',' || str[i] == '.' || str[i] == '?' || str[i] == '/'
				|| str[i] == '<' || str[i] == '>')
			puncts++;
	}
	// Print the number of times the keyword was found
	printf("contains %zu times the word %s.\n", counter, KEY);

	printf("Total characters %zu\n", strlen(lower));
	printf("Total spaces %zu\n", spaces);
	printf("Total punctuations %zu\n", puncts);

	int countHello = count_word(str, "hello");
	printf("\n\nCount the word hello: %i", countHello);
}

// Function definition for initializing string from user input
void initialization(char str[], size_t buffer_size) {
	// Loop through each position in the buffer
	for (size_t i = 0; i < buffer_size; i++) {
		// Read a single character from standard input
		char c = getchar();

		// If newline character is encountered, end of input
		if (c == '\n') {
			str[i] = '\0';  // Add null terminator to end the string
			return;          // Exit function
		}

		// Store the character in the string array
		str[i] = c;
	}
}

// Function definition for converting string to lowercase
void toLower(char str[]) {
	// Loop through each character in the string
	for (size_t i = 0; i < strlen(str); i++)
		// Check if character is uppercase letter (A-Z)
		if ('A' <= str[i] && str[i] <= 'Z') {
			// Convert to zero-based position in alphabet (A=0, B=1, etc.)
			str[i] -= 'A';
			// Convert to lowercase by adding 'a' ASCII value
			str[i] += 'a';
		}
}

int count_word(char text[], char word[]) {
	int count = 0;
	for (int i = 0; i + strlen(word) - 1 < strlen(text); i++) {
		bool testgroup = true; // @suppress("Type cannot be resolved")
		for (int j = 0; j < strlen(word) - 1; j++) {
			if (text[i + j] != word[j]) {
				testgroup = false;
				break;
			}
		}
		if (testgroup)
			count++;
	}
	return count;
}
