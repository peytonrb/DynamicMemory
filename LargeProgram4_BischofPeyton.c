// Peyton Bischof
// Dr. Steinberg
// COP3223 Section 13
// Large Program 4

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char firstName[20];
    char lastName[20];
    char house[20];
    double gpa;
} hogwarts_t;

void populateArray(hogwarts_t database[]);
void display(hogwarts_t database[], int size);
int addRecord(hogwarts_t database[], int element);
void exitProgram(hogwarts_t database[], int element);
int exists(hogwarts_t database[], int element, char fname[], char lname[]);
void removeRecord(hogwarts_t database[], int element);
char *caseSensitivity(char word[]);

int main() {
    int ans = 0;
    int size;
    int doesExist = 1;
    int element = 6;
    char fname[20];
    char lname[20];
    char *fnameCase;
    char *lnameCase;
    hogwarts_t database[30];

    populateArray(database);
    printf("Welcome to the Hogwarts School Database System!\n\n");

    while (ans != 5) {

        // checks for valid input 
        do {
            printf("What action would you like to take?\n");
            printf("1: Add a new record\n");
            printf("2: Remove an existing record\n");
            printf("3: Check for existing record\n");
            printf("4: Display all records\n");
            printf("5: Exit and print record report\n");
            printf("Choice: ");
            scanf("%d", &ans);
            printf("\n");

            if (ans > 5 || ans < 1) {
                printf("Invalid input. Please try again.\n");
            }

        } while (ans > 5 || ans < 1);

        // determines code to compile based on user input
        switch(ans) {
            case 1: 
                element = addRecord(database, element);
                break;
            case 2:
                removeRecord(database, element);
                element--;
                break;
            case 3:
                printf("Which student are you looking for?\n");
                printf("Enter student's first name: ");
                scanf("%s", fname);
                printf("Enter student's last name: ");
                scanf("%s", lname);

                // check for case sensitivity in user input
                fnameCase = caseSensitivity(fname);
                strcpy(fname, fnameCase);
                lnameCase = caseSensitivity(lname);
                strcpy(lname, lnameCase);

                doesExist = exists(database, element, fname, lname); 
                strcat(fname, " ");
                strcat(fname, lname);
                printf("------------------------------------------\n");

                if (doesExist == 1) {
                    printf("\n%s exists in the Hogwarts Student Database!\n\n", fname);
                } else {
                    printf("\n%s does not exist in the Hogwarts Student Databse.\n", fname);
                }
                printf("\n------------------------------------------\n");

                break;
            case 4:
                display(database, element);
                break;
            case 5:
                printf("Now exiting the database.\n");
                exitProgram(database, element);
                break;
        }
    }

    return 0;
}

// adds an entry to the database
// accepts two parameters of type hogwarts_t and integer that contains the database and the number 
//      of active (non-garbage) elements in the array
// returns an integer value of the new length of the array's non-garbage values
int addRecord(hogwarts_t database[], int element) {
    printf("Please enter the first name of the student: ");
    scanf("%s", database[element].firstName);
    printf("Please enter the last name of the student: ");
    scanf("%s", database[element].lastName);
    printf("Please enter the student's house: ");
    scanf("%s", database[element].house);
    printf("Please enter the student's last recorded GPA: ");
    scanf("%lf", &database[element].gpa);
    printf("\n"); // formatting

    printf("------------------------------------------\n\n");
    printf("Student added successfully!\n\n");
    printf("------------------------------------------\n\n");

    element++;
    return element;
}

// removes an existing entry from the database
// accepts two parameters of type hogwarts_t and integer that contains the database and the number 
//      of active (non-garbage) elements in the array
void removeRecord(hogwarts_t database[], int element) {
    char fname[20];
    char lname[20];
    char *fnameCase;
    char *lnameCase;
    int index;

    printf("Which record would you like to remove?\n");
    printf("Enter student's first name: ");
    scanf("%s", fname);
    printf("Enter student's last name: ");
    scanf("%s", lname);

    // check for case sensitivity in user input
    fnameCase = caseSensitivity(fname);
    strcpy(fname, fnameCase);
    lnameCase = caseSensitivity(lname);
    strcpy(lname, lnameCase);

    printf("\n");
    printf("------------------------------------------\n\n");
    // make sure the element trying to remove exists in database
    if (exists(database, element, fname, lname) == 1) {

        // find what index record is at
        for (int i = 0; i < element; i++) {
            if (strcmp(database[i].firstName, fname) == 0 && strcmp(database[i].lastName, lname) == 0) {
                index = i;
            }
        }

        // removes index and shifts proceeding elements over by one index
        for (int j = index; j < element; j++) {
            database[j] = database[j + 1];
        }
        
        printf("Student %s %s deleted successfully!\n\n", fname, lname);

    } else {
        printf("Student does not exist in the Hogwarts School Database.\n");
    }

    printf("------------------------------------------\n\n");
}

// checks if element exists in database with given name
// returns an integer value indicating if the entry exists or not
// accepts four parameters of type hogwarts_t containing the databse, an integer containing the number of 
//      active elements in the database, and two strings containing the first and last name of entry
int exists(hogwarts_t database[], int element, char fname[], char lname[]) {
    int result = 0;

    for (int i = 0; i < element; i++) {
        if (strcmp(database[i].firstName, fname) == 0 && strcmp(database[i].lastName, lname) == 0) {
            result = 1;
        } 
    }

    return result;
}

// creates a file containing the records maintained from the program run
// accepts two parameters of type hogwarts_t and integer that contains the database and the number 
//      of active (non-garbage) elements in the array
void exitProgram(hogwarts_t database[], int element) {
    FILE *records;
    records = fopen("Records.txt", "w");

    fprintf(records, "Hogwarts School Database\n");
    fprintf(records, "------------------------------------------\n");
    for (int i = 0; i < element; i++) {
        fprintf(records, "ID: %d\n", i + 1);
        fprintf(records, "First Name: %s\n", database[i].firstName);
        fprintf(records, "Last Name: %s\n", database[i].lastName);
        fprintf(records, "House: %s\n", database[i].house);
        fprintf(records, "GPA: %0.2lf\n", database[i].gpa);
        fprintf(records, "------------------------------------------\n");
    }

    fclose(records);
}

// displays all the elements currently in the database
// accepts two parameters of type hogwarts_t and integer that contain the database 
//      and the current number of active elements
void display(hogwarts_t database[], int element) {
    printf("------------------------------------------\n");
    for (int i = 0; i < element; i++) {
        printf("ID: %d\n", i + 1);
        printf("First Name: %s\n", database[i].firstName);
        printf("Last Name: %s\n", database[i].lastName);
        printf("House: %s\n", database[i].house);
        printf("GPA: %0.2lf\n", database[i].gpa);
        printf("------------------------------------------\n");
    }
    
    printf("\n"); // formatting
}

// passes user input through to validate proper case sensitivity in database
// accepts one parameter of type string that contains the word requiring updating
char *caseSensitivity(char word[]) {
    char formattedWord[20];
    char *returnWord;
    strcpy(formattedWord, word);
    formattedWord[0] = toupper(word[0]);

    for (int i = 1; i < strlen(word); i++) {
        formattedWord[i] = tolower(word[i]);
    }

    returnWord = formattedWord;

    return returnWord;
}

// hardcoding the database's first six elements upon program run
// accepts one parameter of type hogwarts_t that contains the database
void populateArray(hogwarts_t database[]) {
    database[0].id = 1;
    strcpy(database[0].firstName, "Harry");
    strcpy(database[0].lastName, "Potter");
    strcpy(database[0].house, "Gryffindor");
    database[0].gpa = 3.81;

    database[1].id = 2;
    strcpy(database[1].firstName, "Ronald");
    strcpy(database[1].lastName, "Weasley");
    strcpy(database[1].house, "Gryffindor");
    database[1].gpa = 2.64;

    database[2].id = 3;
    strcpy(database[2].firstName, "Hermione");
    strcpy(database[2].lastName, "Granger");
    strcpy(database[2].house, "Gryffindor");
    database[2].gpa = 4.00;

    database[3].id = 4;
    strcpy(database[3].firstName, "Draco");
    strcpy(database[3].lastName, "Malfoy");
    strcpy(database[3].house, "Slytherin");
    database[3].gpa = 3.56;

    database[4].id = 5;
    strcpy(database[4].firstName, "Luna");
    strcpy(database[4].lastName, "Lovegood");
    strcpy(database[4].house, "Ravenclaw");
    database[4].gpa = 2.82;

    database[5].id = 6;
    strcpy(database[5].firstName, "Ginny");
    strcpy(database[5].lastName, "Weasley");
    strcpy(database[5].house, "Gryffindor");
    database[5].gpa = 3.67;
}