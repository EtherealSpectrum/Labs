// ΚΑΚΟΥΛΛΗΣ 1117202500063

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_STUDENTS 5
#define TOTAL_GRADES 10
#define FILENAME "results.txt"

// Χρήση typedef για απλούστευση της δήλωσης της δομής
typedef struct {
	char name[50];
	int am;
	int grades[TOTAL_GRADES];
	float avg;
} Student;

// Συνάρτηση για την εκτύπωση των αποτελεσμάτων (στην οθόνη και σε αρχείο)
void print_results(Student students[], FILE *fp) {
	// Εκτύπωση επικεφαλίδων

	fprintf(fp, "-------------------------\n");
	fprintf(fp, "%-15s %-5s\n", "|Name ", " |Avg   |");
	fprintf(fp, "-------------------------\n");

	// Εκτύπωση δεδομένων με ακρίβεια ενός δεκαδικού ψηφίου (%.1f)
	for (int i = 0; i < TOTAL_STUDENTS; i++) {
		fprintf(fp, "|%-15s | %-5.1f|\n", students[i].name,
				students[i].avg);
		fprintf(fp, "-------------------------\n");
	}
	fprintf(fp, "\n\n");
}

// Συνάρτηση Selection Sort (ταξινόμηση σε φθίνουσα σειρά κατά μέσο όρο)
void selection_sort_students(Student students[]) {
	int i, j, max_idx;
	Student temp; // Προσωρινή δομή για τη swap

	for (i = 0; i < TOTAL_STUDENTS - 1; i++) {
		max_idx = i;
		for (j = i + 1; j < TOTAL_STUDENTS; j++) {
			if (students[j].avg > students[max_idx].avg) {
				max_idx = j;
			}
		}
		// Ανταλλαγή (swap) των δομών
		temp = students[max_idx];
		students[max_idx] = students[i];
		students[i] = temp;
	}
}

// Συνάρτηση Bubble Sort (ταξινόμηση σε φθίνουσα σειρά κατά μέσο όρο)
void bubble_sort_students(Student students[]) {
	int i, j;
	Student temp; // Προσωρινή δομή για τη swap

	for (i = 0; i < TOTAL_STUDENTS - 1; i++) {
		for (j = 0; j < TOTAL_STUDENTS - i - 1; j++) {
			if (students[j].avg < students[j + 1].avg) {
				// Ανταλλαγή (swap) των δομών
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
}

int main() {
	Student students[TOTAL_STUDENTS];
	int i, j, sum;
	FILE *fp; // @suppress("Type cannot be resolved")

	// --- ΜΕΡΟΣ ΕΙΣΑΓΩΓΗΣ ΣΤΟΙΧΕΙΩΝ & ΥΠΟΛΟΓΙΣΜΟΥ Μ.Ο. ---
	for (i = 0; i < TOTAL_STUDENTS; i++) {
		printf("--- Insert student informations %d ---\n", i + 1);
		printf("Name: ");
		scanf(" %[^\n]s", students[i].name);

		printf("Reg Numb: ");
		scanf("%d", &students[i].am);

		sum = 0;
		printf("Insert your %d grades:\n", TOTAL_GRADES);
		for (j = 0; j < TOTAL_GRADES; j++) {
			printf("Grade %d: ", j + 1);
			scanf("%d", &students[i].grades[j]);
			sum += students[i].grades[j];
		}
		students[i].avg = ((float) sum) / TOTAL_GRADES;
		printf("\n");
	}

	getchar(); //Consume the new line.

	// --- ΜΕΡΟΣ Α: ΕΚΤΥΠΩΣΗ ΑΡΧΙΚΩΝ ΑΠΟΤΕΛΕΣΜΑΤΩΝ ---
	printf("\n\n--- Initial Results ---\n");
	printf("-------------------------------------------\n");
	for (i = 0; i < TOTAL_STUDENTS; i++) {
		printf("|Name: %-15s |REG NUM: %-5d |AVG: %.1f |\n", students[i].name,
				students[i].am, students[i].avg);
		printf("-------------------------------------------\n");
	}

	// --- ΜΕΡΟΣ Β
	printf("Selection/Bubble sort? (s/b): ");
	char option = getchar();
	switch (option) {
	case 's':
	// (α): ΤΑΞΙΝΟΜΗΣΗ ΜΕ SELECTION SORT ---
	selection_sort_students(students);
	printf("\n--- Results after Selection Sort (Fthinousa seira) ---\n");
	break;
	case 'b':
	//(β): ΤΑΞΙΝΟΜΗΣΗ ΜΕ BUBBLE SORT ---
	bubble_sort_students(students);
	printf("\n--- Results after bubble sort (Fthinousa seira) ---\n");
	break;
	}

	print_results(students, stdout); // Εκτύπωση στην κονσόλα (stdout)

	// --- ΜΕΡΟΣ Γ: ΑΠΟΘΗΚΕΥΣΗ ΣΕ ΑΡΧΕΙΟ results.txt ---
	// Ανοίγει το αρχείο σε λειτουργία "w" (write), αντικαθιστώντας το αν υπάρχει
	fp = fopen(FILENAME, "w");
	if (fp == NULL) {
		printf("Error can't open the file %s\n", FILENAME);
		return EXIT_FAILURE;
	}
	fprintf(fp, "Student Results (Ordered with Bubble Sort):\n");
	print_results(students, fp); // Εκτύπωση στο αρχείο
	fclose(fp); // Κλείσιμο αρχείου
	printf("The ordered results are saved successfully in %s\n", FILENAME);

	return EXIT_SUCCESS;
}
