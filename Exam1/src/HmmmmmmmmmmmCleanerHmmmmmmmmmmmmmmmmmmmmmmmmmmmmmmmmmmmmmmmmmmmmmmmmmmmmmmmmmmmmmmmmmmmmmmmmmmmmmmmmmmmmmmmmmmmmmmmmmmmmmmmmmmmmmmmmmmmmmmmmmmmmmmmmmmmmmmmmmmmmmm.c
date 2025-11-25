#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int digitSum(int n);
unsigned int digitalRoot(int n);
bool is_single_digit(int n);
bool isPrime(int n);

/*--------------------------------------------------------------*/
/*  PRIME CHECK                                                  */
/*--------------------------------------------------------------*/
bool isPrime(int n) {
    if (n < 0) n = -n;
    if (n <= 1) return false;
    if (n <= 3) return true;

    if (n % 2 == 0 || n % 3 == 0) 
        return false;

    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

/*--------------------------------------------------------------*/
/*  MAIN                                                         */
/*--------------------------------------------------------------*/
int main(void) {
    int sizeList;

    printf("Give the size of the list: ");
    if (scanf("%d", &sizeList) != 1 || sizeList <= 0) {
        printf("Invalid list size.\n");
        return 1;
    }

    for (int i = 0; i < sizeList; i++) {
        printf("\nTime: i = %d\n\n", i + 1);

        int number;
        printf("Enter an integer number (not zero): ");

        while (true) {
            if (scanf("%d", &number) == 1 && number != 0)
                break;

            printf("Invalid number.\n");
            printf("Error Message: Non-zero number required.\n");
            printf("Please try again: ");
            while (getchar() != '\n');  // Clear input buffer
        }

        int dgroot = digitalRoot(number);

        printf("\nThe digital root of the number %d is: %d\n\n",
               number, dgroot);

        if (dgroot == 5) {
            printf("Number %d is %sprime\n\n",
                   number, isPrime(number) ? "" : "not ");
        }
    }

    return 0;
}

/*--------------------------------------------------------------*/
/*  DIGIT SUM                                                    */
/*--------------------------------------------------------------*/
unsigned int digitSum(int n) {
    if (n < 0) n = -n;

    unsigned int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

/*--------------------------------------------------------------*/
/*  DIGITAL ROOT WITH TRACE ARRAY                                */
/*--------------------------------------------------------------*/
unsigned int digitalRoot(int n) {
    int original = n;
    if (n < 0) n = -n;

    int chain[20];        // Enough for any 32-bit integer
    int length = 0;

    chain[length++] = original;

    int current = n;
    while (!is_single_digit(current)) {
        current = digitSum(current);
        chain[length++] = current;
    }

    printf("Elements of the array: ");
    for (int i = 0; i < length; i++)
        printf("%d ", chain[i]);
    printf("\n");

    int sumElements = 0;
    for (int i = 0; i < length; i++)
        sumElements += chain[i];

    printf("The sum of the elements is: %d\n", sumElements);

    return current;
}

/*--------------------------------------------------------------*/
/*  SINGLE DIGIT CHECK                                           */
/*--------------------------------------------------------------*/
bool is_single_digit(int number) {
    if (number < 0) number = -number;
    return number <= 9;
}
