/*****************************************************************
 // Name:        Wyatt Bartlett
 //
 // Homework:    3
 //
 // Class:       ICS 212
 //
 // Instructor:  Ravi Narayan
 //
 // Date:        February 7, 2016
 //
 // File:        UI.c
 //
 // Description: The file contains the user-interface functions for HW3, the fake
 //              database assignment.
 //
 //
 //***************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "record.h"
#include "func.h"

#define MINYEAR 1
#define MAXYEAR 10000
#define MAXADDRESS 80
#define MAXNAME 25

int debugmode = 0;

int main(int argc, char *argv[]) {
    struct record *start = NULL;
    char * storage = "storage.txt";
    int choice = 0;
    int accountno = 0;
    char name[MAXNAME];
    char address[MAXADDRESS];
    int yearofbirth = 0;
    char fieldChoice[80] = "";
    int recordsAccessed = 0;

    strncpy(name, "", (MAXNAME - 1));
    strncpy(address, "", (MAXADDRESS - 1));

    checkDebugMode(argc, argv);
    readfile(&start, storage);

    while (choice != 6) {
        displayMenu();
        choice = getChoice();
        switch (choice) {
        case 1:
            puts("       1:   Add Record");
            accountno = getAccountNo();
            getName(name, MAXNAME);
            getfield(address, MAXADDRESS);
            yearofbirth = getBirthYear();
            addRecord(&start, accountno, name, address, yearofbirth);
            puts("Adding record...");
            puts("Record added.");
            break;
        case 2:
            puts("       2:   Modify Record");
            if (!isListEmpty(start)) {
                accountno = getAccountNo();
                getfield(address, MAXADDRESS);
                puts("Modifying record(s)...");
                recordsAccessed = modifyRecord(start, accountno, address);
                if (recordsAccessed > 0) {
                    printf("%d record(s) modified.\n", recordsAccessed);
                    recordsAccessed = 0;
                } else {
                    puts("\nSorry... the record could not be modified, because "
                            "it could not be found.");
                }
            } else {
                puts("\nSorry... There are no records to modify.");
            }
            break;
        case 3:
            puts("       3:   Print Record");
            if (!isListEmpty(start)) {
                accountno = getAccountNo();
                puts("Printing record(s)...\n");
                recordsAccessed = printRecord(start, accountno);
                if (recordsAccessed > 0) {
                    printf("%d record(s) printed.\n", recordsAccessed);
                    recordsAccessed = 0;
                } else {
                    puts("\nSorry... the record could not be printed, because "
                            "it could not be found.");
                }
            } else {
                puts("\nSorry... There are no records to print.");
            }
            break;
        case 4:
            puts("       4:   Print All Records");
            if (!isListEmpty(start)) {
                puts("\nPrinting all records...\n\n");
                printAllRecords(start);
                puts("\nAll records printed.");
            } else {
                puts("\nSorry... There are no records to print.");
            }
            break;
        case 5:
            puts("       5:   Delete Record");
            if (!isListEmpty(start)) {
                accountno = getAccountNo();
                puts("Deleting record(s)...");
                recordsAccessed = deleteRecord(&start, accountno);
                if (recordsAccessed > 0) {
                    printf("%d record(s) deleted.\n", recordsAccessed);
                    recordsAccessed = 0;
                } else {
                    puts("\nSorry... the record could not be deleted, because "
                            "it could not be found.");
                }
            } else {
                puts("\nSorry... There are no records to delete.");
            }
            break;
        case 6:
            puts("       6:   Quit");
            puts("Closing program...");
            writefile(start, storage);
            cleanup(start);
            puts("Goodbye!");
        }/* end switch */

    }/* end while loop */

    return 0;
} /* end main */

/*****************************************************************
 //
 // Function name:   checkDebugMode
 //
 // DESCRIPTION:     This function checks if debug mode has been activated and
 //                  returns an error if the arguments for project1 are invalid.
 //
 // Parameters:      numArgs (int) :         the array of record pointers
 //                  argStrings (char*[]) :  the account no. of the customer
 //
 // Return values:   NONE
 //
 //****************************************************************/
void checkDebugMode(int numArgs, char* argStrings[]) {
    if (numArgs == 2 && (strcmp(argStrings[1], "debug") == 0)) {
        debugmode = 1;
        puts("**DEBUG MODE ACTIVATED**");
        puts("");
        puts("");
        puts("**DEBUG**");
        puts("Function name: checkDebugMode");
        printf("Parameters: numArgs = %i, argStrings = %u", numArgs,
                argStrings);
        puts("");
        puts("");
    } else if (numArgs == 1) {
        debugmode = 0;
    } else {
        int i;
        /*raise error*/
        printf("project1: Invalid arguments (");
        for (i = 1; i < numArgs; i++) {
            printf(" %s ", argStrings[i]);
        }
        printf(")");
        puts("");
        puts("Usage: project1");
        puts("       project1 debug");
        exit (EXIT_FAILURE);
    }
}

/*****************************************************************
 //
 // Function name:   isListEmpty
 //
 // DESCRIPTION:     This function checks if the LinkedList is empty or not.
 //
 // Parameters:      start (struct record *) :  a pointer to the start of the
 //                                             LinkedList
 //
 // Return values:  1 if the list is empty
 //                 0 otherwise
 //
 //****************************************************************/
int isListEmpty(struct record * start) {
    int status;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: isListEmpty");
        printf("Parameters: start = %u", start);
        puts("");
        puts("");
    }

    if (start == NULL) {
        status = 1;
    } else {
        status = 0;
    }
    return status;
}

/*****************************************************************
 //
 // Function name:   displayMenu
 //
 // DESCRIPTION:     This function displays the menu options for the user.
 //
 // Parameters:      NONE
 //
 // Return values:   NONE
 //
 //****************************************************************/
void displayMenu() {
    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: displayMenu");
        printf("Parameters: NONE");
        puts("");
        puts("");
    }

    puts("");
    printf("----------------------------------------\n");
    puts("Menu:");
    puts("");
    puts("Option #");
    puts("       1:   Add Record");
    puts("       2:   Modify Record");
    puts("       3:   Print Record");
    puts("       4:   Print All Records");
    puts("       5:   Delete Record");
    puts("       6:   Quit");
    printf("----------------------------------------\n");
    puts("");
}

/*****************************************************************
 //
 // Function name:  getChoice
 //
 // DESCRIPTION:    A user interface function. This function obtains the number
 //                 representing the user's selected menu option.
 //
 // Parameters:     NONE
 //
 // Return values:  Returns the user input if it is a valid integer greater than
 //                 zero.
 //
 //****************************************************************/
int getChoice() {
    int i, input;
    char str[25] = "";
    i = 0;
    input = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: getChoice");
        printf("Parameters: NONE");
        puts("");
        puts("");
    }

    printf("Please select an option by typing in the associated option #, then "
            "pressing the ENTER key. Options are represented by numbers "
            "1-6: ");
    scanf("%24s", &str);
    eatTrash();
    input = atoi(str);

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            if (input < 1 || input > 6) {
                printf("Sorry... please enter a number from 1 to 6: ");
                scanf("%24s", &str);
                eatTrash();
                input = atoi(str);
                i = 0;
            } else {
                i++;
            }
        } else {
            printf("Sorry... please enter a number from 1 to 6: ");
            scanf("%24s", &str);
            eatTrash();
            input = atoi(str);
            i = 0;
        }
    }
    puts("");
    printf("Input accepted: %d\n\n", input);
    puts("");
    puts("");
    return input;
}

/*****************************************************************
 //
 // Function name:  getAccountNo
 //
 // DESCRIPTION:    A user interface function. This function obtains the user's
 //                 account number.
 //
 // Parameters:     NONE
 //
 // Return values:  Returns the user input if it is a valid integer greater than
 //                 zero.
 //
 //****************************************************************/
int getAccountNo() {
    int i, input;
    char str[10] = "";
    i = 0;
    input = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: getAccountNo");
        printf("Parameters: NONE");
        puts("");
        puts("");
    }

    printf("Please enter the customer's account number (greater than zero) "
            "followed by the ENTER key: ");
    scanf("%9s", &str);
    eatTrash();
    input = atoi(str);

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            if (input <= 0) {
                printf("Sorry... please enter a number greater than zero: ");
                scanf("%9s", &str);
                eatTrash();
                input = atoi(str);
                i = 0;
            } else {
                i++;
            }
        } else {
            printf("Sorry... please enter an account number: ");
            scanf("%9s", &str);
            eatTrash();
            input = atoi(str);
            i = 0;
        }
    }
    puts("");
    printf("Input accepted: %d\n\n", input);
    puts("");
    puts("");
    return input;
}

/*****************************************************************
 //
 // Function name:   getName
 //
 // DESCRIPTION:     This function gets the name that the user inputs.
 //
 // Parameters:      field (char[]) :      the field to update
 //                  maxLength (int) :     the maximum number of characters + 2
 //
 // Return values:   NONE
 //
 //****************************************************************/
void getName(char field[], int maxLength) {
    char inString[25];

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: getName");
        printf("Parameters: field = %u, maxLength = %d", field, maxLength);
        ;
        puts("");
        puts("");
    }

    strncpy(inString, "", (maxLength - 1));
    printf("Please enter the customer's name (up to %d characters long) "
            "followed by the ENTER key: ", (maxLength - 2));
    fgets(inString, maxLength, stdin);
    removeTrailingSpace(inString);

    strncpy(field, inString, (maxLength - 1));
    puts("");
    printf("Input accepted: %s\n\n", field);
    puts("");
    puts("");
}

/*****************************************************************
 //
 // Function name:  getfield
 //
 // DESCRIPTION:    This function gets the address that the user inputs.
 //
 // Parameters:     field (char[]) :    the field to update
 //                 maxLength (int) :   the maximum number of characters + 2
 //
 // Return values:  NONE
 //
 //****************************************************************/
void getfield(char field[], int maxLength) {
    char inString[80];
    char tempString[80] = "\0";
    int c = 0;
    int carrot = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: getfield");
        printf("Parameters: field = %u, maxLength = %d", field, maxLength);
        ;
        puts("");
        puts("");
    }

    strncpy(inString, "", (maxLength - 1));

    printf("Please enter the customer's address (up to %d characters long) "
            "followed by the '^' key and then the ENTER key: ",
            (maxLength - 2));
    puts("");
    while ((carrot != 1 && (strlen(inString) < (maxLength - 1)))) {
        c = fgetc(stdin);
        if (c != 94) {
            tempString[0] = (char) c;
            strcat(inString, tempString);
        } else {
            carrot = 1;
        }
    }
    removeTrailingSpace(inString);
    strncpy(field, inString, (maxLength - 1));
    eatTrash();
    puts("");
    printf("Input accepted: \n%s\n\n", field);
    puts("");
    puts("");
}

/*****************************************************************
 //
 // Function name:  getBirthYear
 //
 // DESCRIPTION:    A user interface function. This function obtains the user's
 //                 year of birth.
 //
 // Parameters:     NONE
 //
 // Return values:  Returns the user input if it is a valid integer greater than
 //                 zero and less than 10000.
 //
 //****************************************************************/
int getBirthYear() {
    int i, input;
    char str[6] = "";
    i = 0;
    input = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: getBirthYear");
        printf("Parameters: NONE");
        puts("");
        puts("");
    }

    printf("Please enter the customer's year of birth followed by the ENTER "
            "key: ");
    scanf("%5s", &str);
    eatTrash();
    input = atoi(str);

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            if (input < (MINYEAR) || input >= MAXYEAR) {
                printf("Sorry... please enter a year greater than %i and "
                        "less than %i: ", (MINYEAR - 1), MAXYEAR);
                scanf("%5s", &str);
                eatTrash();
                input = atoi(str);
                i = 0;
            } else {
                i++;
            }
        } else {
            printf("Sorry... please enter a year: ");
            scanf("%5s", &str);
            eatTrash();
            input = atoi(str);
            i = 0;
        }
    }
    puts("");
    printf("Input accepted: %d\n\n", input);
    puts("");
    puts("");
    return input;
}

/*****************************************************************
 //
 // Function name:   chooseField
 //
 // DESCRIPTION:     This function gets the users choice of name or address.
 //
 // Parameters:      fieldChoice (char[]) :  the field to update
 //                  name (char[]) :         the name field
 //                  address (char[]) :      the address field
 //
 // Return values:   NONE
 //
 //****************************************************************/
void chooseField(char fieldChoice[], char name[], char address[]) {

    int i, input;
    char str[2] = "";
    i = 0;
    input = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: chooseField");
        printf("Parameters: fieldChoice = %u, name = %u ", fieldChoice, name);
        printf("address = %u", address);
        puts("");
        puts("");
    }

    /*check input...*/
    puts("Which field would you like to modify?");
    printf("Enter 1 for name, or 2 for address, followed by the ENTER key: ");
    scanf("%1s", &str);
    eatTrash();
    input = atoi(str);

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            if (input < 1 || input > 2) {
                printf("Sorry... please enter either 1 or 2: ");
                scanf("%1s", &str);
                eatTrash();
                input = atoi(str);
                i = 0;
            } else {
                i++;
            }
        } else {
            printf("Sorry... please enter a positive number: ");
            scanf("%1s", &str);
            eatTrash();
            input = atoi(str);
            i = 0;
        }
    }
    puts("");
    printf("Input accepted: %d\n\n", input);
    puts("");
    puts("");

    if (input == 1) {
        getName(name, MAXNAME);
        strncpy(fieldChoice, name, (MAXNAME - 1));
    } else if (input == 2) {
        getfield(address, MAXADDRESS);
        strncpy(fieldChoice, address, (MAXADDRESS - 1));
    } else {
        puts("Unable to update field!");
    }
}

/*****************************************************************
 //
 // Function name:  removeTrailingSpace
 //
 // DESCRIPTION:    This function removes any trailing space from the end of a
 //                 given string (including newline characters).
 //
 // Parameters:     string (char[]):    the given string from which to remove
 //                                     the newline character
 //
 // Return values:  NONE
 //
 //****************************************************************/
void removeTrailingSpace(char string[]) {
    int i;
    char temp[100];
    char c;
    int copychars = strlen(string);
    strncpy(temp, "", 99);

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: removeTrailingSpace");
        printf("Parameters: string = %s", string);
        puts("");
        puts("");
    }

    c = string[(copychars - 1)];

    while (isspace((int) c)) {
        copychars = copychars - 1;
        c = string[(copychars - 1)];
    }

    for (i = 0; i < (copychars); i++) {
        temp[i] = string[i];
    }
    strncpy(string, temp, strlen(string));
}

/*****************************************************************
 //
 // Function name:  eatTrash
 //
 // DESCRIPTION:    This function eats all remaining input from stdin up to and
 //                 including the first '\n'.
 //
 // Parameters:     NONE
 //
 // Return values:  NONE
 //
 //****************************************************************/
void eatTrash() {
    char temp = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: eatTrash");
        printf("Parameters: NONE");
        puts("");
        puts("");
    }

    temp = fgetc(stdin);
    while (temp != '\n') {
        temp = fgetc(stdin);
    }
}
