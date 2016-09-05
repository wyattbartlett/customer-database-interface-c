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
 // File:        DB.c
 //
 // Description: The file that contains the database functions for HW 3, the fake
 //              database assignment.
 //
 //
 //***************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"
#include "func.h"

#define MAXADDRESS 80
#define MAXNAME 25
extern int debugmode;

/*****************************************************************
 //
 // Function name:   addRecord
 //
 // DESCRIPTION:     A database function. This function allows the user to add a
 //                  record to the database.
 //
 // Parameters:      startptr (record **) : the pointer to the start pointer,
 //                                         which points to the start of the
 //                                         list
 //                  uaccountno (int) :     the account no. of the customer
 //                  uname (char []) :      the name of the customer
 //                  uaddr (char []) :      the address of the customer
 //                  uyob (int) :           the year of the customer's birth
 //
 // Return values:   0 if successful
 //                 -1 otherwise
 //
 //****************************************************************/
int addRecord(struct record **startptr, int uaccountno, char uname[],
        char uaddr[], int uyob) {

    /* Create a record */
    struct record *newRecord = NULL;
    int found = -2;
    newRecord = malloc(sizeof(struct record));

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: addRecord");
        printf("Parameters: startptr = %u, uaccountno = %i, ", startptr,
                uaccountno);
        printf("uname = %s, uaddr = %s, uyob = %i", uname, uaddr, uyob);
        puts("");
        puts("");
    }

    /* Fill the record */
    (*newRecord).accountno = uaccountno;
    strncpy((*newRecord).name, uname, MAXNAME);
    strncpy((*newRecord).address, uaddr, MAXADDRESS);
    (*newRecord).yearofbirth = uyob;
    (*newRecord).next = NULL;

    /* Find position and add the record to the LinkedList */
    if (*startptr == NULL) {
        *startptr = newRecord;
        found = 0;
    } else if ((*startptr) != NULL) {
        struct record * currentRecord;
        currentRecord = *startptr;
        found = -2;

        if ((*newRecord).accountno <= (**startptr).accountno) {
            (*newRecord).next = *startptr;
            *startptr = newRecord;
            found = 0;
        }

        while ((*currentRecord).next != NULL && found != 0) {

            if ((*newRecord).accountno
                    <= (*((*currentRecord).next)).accountno) {
                (*newRecord).next = (*currentRecord).next;
                (*currentRecord).next = newRecord;
                found = 0;
            }

            if ((*newRecord).accountno > (*((*currentRecord).next)).accountno) {
                currentRecord = (*currentRecord).next;
            }

        }

        if (found == -2) {
            (*currentRecord).next = newRecord;
            found = 0;
        }
    }
    return found;
}

/*****************************************************************
 //
 // Function name:   modifyRecord
 //
 // DESCRIPTION:     A database function. This function allows the user to
 //                  modify a record that is held within the database.
 //
 // Parameters:      start (record *) :     a record pointer
 //                  uaccountno (int) :     the account no. of the customer
 //                  input (char []) :      the user input to be used to update
 //                                         the appropriate field
 //
 // Return values:   0 if successful
 //                 -1 otherwise
 //
 //****************************************************************/
int modifyRecord(struct record *start, int uaccountno, char input[]) {
    int found = 0;
    int done = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: modifyRecord");
        printf("Parameters: start = %u, uaccountno = %i, ", start, uaccountno);
        printf("input = %s", input);
        puts("");
        puts("");
    }

    if (start != NULL) {
        struct record *currentRecord;
        currentRecord = start;

        if ((*start).accountno == uaccountno) {

            while (currentRecord != NULL && done != 1) {
                if ((*currentRecord).accountno == uaccountno) {
                    strncpy((*currentRecord).address, input, 80);
                    currentRecord = (*currentRecord).next;
                    found = found + 1;
                } else {
                    done = 1;
                }
            }

        } else {
            if ((*currentRecord).next != NULL) {
                currentRecord = (*currentRecord).next;
                while (currentRecord != NULL) {
                    if ((*currentRecord).accountno == uaccountno) {
                        strncpy((*currentRecord).address, input, 80);
                        currentRecord = (*currentRecord).next;
                        found = found + 1;
                    } else if ((*currentRecord).accountno != uaccountno) {
                        currentRecord = (*currentRecord).next;
                    }
                }
            }
        }
    }
    return found;
}

/*****************************************************************
 //
 // Function name:   printRecord
 //
 // DESCRIPTION:     A database function. This function allows the user to print
 //                  a record that is held within the database.
 //
 // Parameters:      start (record *) :     a record pointer to the start of
 //                                         the Linked List
 //                  uaccountno (int) :     the account no. of the customer
 //
 // Return values:   0 if successful
 //                 -1 otherwise
 //
 //****************************************************************/
int printRecord(struct record *start, int uaccountno) {
    int found = 0;
    int done = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: printRecord");
        printf("Parameters: start = %u, uaccountno = %i, ", start, uaccountno);
        puts("");
        puts("");
    }

    if (start != NULL) {
        struct record *currentRecord;
        currentRecord = start;

        if ((*start).accountno == uaccountno) {

            while (currentRecord != NULL && done != 1) {
                if ((*currentRecord).accountno == uaccountno) {
                    fprintf(stdout, "%i\n", (*currentRecord).accountno);
                    fprintf(stdout, "%s\n", (*currentRecord).name);
                    fprintf(stdout, "%s\n", (*currentRecord).address);
                    fprintf(stdout, "%i\n", (*currentRecord).yearofbirth);
                    puts("");
                    currentRecord = (*currentRecord).next;
                    found = found + 1;
                } else {
                    done = 1;
                }
            }

        } else {
            if ((*currentRecord).next != NULL) {
                currentRecord = (*currentRecord).next;
                while (currentRecord != NULL) {
                    if ((*currentRecord).accountno == uaccountno) {
                        fprintf(stdout, "%i\n", (*currentRecord).accountno);
                        fprintf(stdout, "%s\n", (*currentRecord).name);
                        fprintf(stdout, "%s\n", (*currentRecord).address);
                        fprintf(stdout, "%i\n", (*currentRecord).yearofbirth);
                        puts("");
                        currentRecord = (*currentRecord).next;
                        found = found + 1;
                    } else if ((*currentRecord).accountno != uaccountno) {
                        currentRecord = (*currentRecord).next;
                    }
                }
            }
        }
    }
    return found;
}

/*****************************************************************
 //
 // Function name:   printAllRecords
 //
 // DESCRIPTION:     A database function. This function allows the user to print
 //                  all of the records that are held within the database.
 //
 // Parameters:      firstEntry (record *) :     a pointer to the first record
 //
 // Return values:   NONE
 //
 //****************************************************************/
void printAllRecords(struct record *firstEntry) {
    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: printAllRecords");
        printf("Parameters: firstEntry = %u", firstEntry);
        puts("");
        puts("");
    }

    if ((firstEntry) != NULL) {
        struct record * currentRecord;
        currentRecord = firstEntry;

        while (currentRecord != NULL) {
            fprintf(stdout, "%i\n", (*currentRecord).accountno);
            fprintf(stdout, "%s\n", (*currentRecord).name);
            fprintf(stdout, "%s\n", (*currentRecord).address);
            fprintf(stdout, "%i\n", (*currentRecord).yearofbirth);
            puts("");
            currentRecord = (*currentRecord).next;
        }
    }

}

/*****************************************************************
 //
 // Function name:   deleteRecord
 //
 // DESCRIPTION:     A database function. This function allows the user to modify
 //                  a record that is held within the database.
 //
 // Parameters:      startptr (record **) : the pointer to the start pointer,
 //                                         which points to the start of the
 //                                         list
 //                  uaccountno (int) :     the account no. of the customer
 //
 // Return values:   0 if successful
 //                 -1 otherwise
 //
 //****************************************************************/
int deleteRecord(struct record **startptr, int uaccountno) {
    int found = 0;
    int done = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: deleteRecord");
        printf("Parameters: startptr = %u, uaccountno = %i, ", startptr,
                uaccountno);
        puts("");
        puts("");
    }

    if (*startptr != NULL) {

        if ((**startptr).accountno == uaccountno) {

            while (*startptr != NULL && done != 1) {
                if ((**startptr).accountno == uaccountno) {
                    struct record *tempRecord;
                    tempRecord = *startptr;
                    *startptr = (**startptr).next;
                    (*tempRecord).next = NULL;
                    free(tempRecord);
                    found = found + 1;
                } else {
                    done = 1;
                }
            }

        } else {
            if ((**startptr).next != NULL) {
                struct record *previous = *startptr;
                struct record *current = (**startptr).next;

                while (current != NULL) {
                    if ((*current).accountno == uaccountno) {
                        struct record *temp;
                        (*previous).next = (*current).next;
                        (*current).next = NULL;
                        temp = current;
                        current = (*previous).next;
                        free(temp);
                        found = found + 1;
                    } else if ((*current).accountno != uaccountno) {
                        current = (*current).next;
                        previous = (*previous).next;
                    }
                }
            }
        }
    }
    return found;
}

/*****************************************************************
 //
 // Function name:   cleanup
 //
 // DESCRIPTION:     A database function. This function wipes the entire
 //                  Linked List clean.
 //
 // Parameters:      start (record *) :     a pointer to the first record
 //
 // Return values:   NONE
 //
 //****************************************************************/
void cleanup(struct record *start) {
    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: cleanup");
        printf("Parameters: start = %u", start);
        puts("");
        puts("");
    }

    if ((start) != NULL) {
        struct record * currentRecord;
        currentRecord = start;

        while (currentRecord != NULL) {
            struct record * tempRecord;
            tempRecord = (*currentRecord).next;
            free(currentRecord);
            currentRecord = tempRecord;
        }
    }

}
