/*****************************************************************
 // Name:        Wyatt Bartlett
 //
 // Homework:    5
 //
 // Class:       ICS 212
 //
 // Instructor:  Ravi Narayan
 //
 // Date:        February 25, 2016
 //
 // File:        iofunctions.c
 //
 // Description: The file contains the I/O functions for HW5.
 //
 //***************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include "record.h"
#include "func.h"

#define MAXADDRESS 80
#define MAXNAME 25

extern int debugmode;

/*****************************************************************
 //
 // Function name:  readfile
 //
 // DESCRIPTION:    This function reads in from a file and stores what is read
 //                 in the nodes of the linkedList.
 //
 // Parameters:     linkedList (record**):  a LinkedList of records to read into
 //                 filename (char[]):      a string containing the name of the
 //                                         file to read from
 //
 // Return values:  0: if successful
 //				   -1: if an error occurs
 //
 //****************************************************************/
int readfile(struct record **linkedList, char filename[]) {
    char file[100] = "\0";
    char line[100] = "\0";
    char empty[2] = "";
    FILE * infilebuffer;
    int status;
    int accountno;
    char name[MAXNAME];
    char address[MAXADDRESS];
    int yearofbirth;
    char tempString[2] = "\0"; /* gives {\0, \0} */
    int c = 0;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: readfile");
        printf("Parameters: linkedList = %u, filename = %s, ", linkedList,
                filename);
        puts("");
        puts("");
    }

    strncpy(file, filename, 99);
    infilebuffer = fopen(file, "r");

    if (infilebuffer != NULL) {

        while (!feof(infilebuffer)) {
            strncpy(line, empty, 10);
            fgets(line, 9, infilebuffer);
            if (!feof(infilebuffer)) {

                removeTrailingSpace(line);
                accountno = atoi(line);

                strncpy(line, empty, 10);
                fgets(line, 99, infilebuffer);
                removeTrailingSpace(line);
                strncpy(name, line, (MAXNAME - 1));

                strncpy(line, empty, 10);
                while ((c != 94)) {
                    c = fgetc(infilebuffer);
                    if (c != 94) {
                        tempString[0] = (char) c;
                        strcat(line, tempString);
                    }
                }
                strncpy(address, line, (MAXADDRESS - 1));
                while ((c != 10)) {
                    c = fgetc(infilebuffer);
                }

                strncpy(line, empty, 10);
                fgets(line, 99, infilebuffer);
                removeTrailingSpace(line);
                yearofbirth = atoi(line);

                addRecord(linkedList, accountno, name, address, yearofbirth);
            }

        }
        status = 0;
        fclose(infilebuffer);
    } else {
        status = -1;
    }

    return (status);
}

/*****************************************************************
 //
 // Function name:  writefile
 //
 // DESCRIPTION:    This function writes out each field of the records in the
 //                 LinkedList (in which start is the first node) to a file. If
 //                 the file already exists, it is overwritten.
 //
 // Parameters:     start (record *):       the start of the LinkedList to write
 //                                         from
 //                 filename (char[]):      a string containing the name of the
 //                                         file to write to
 //
 // Return values:  0: if successful
 //                -1: if an error occurs
 //
 //****************************************************************/
void writefile(struct record *start, char filename[]) {
    char file[100];
    FILE * outfilebuffer;

    if (debugmode == 1) {
        puts("");
        puts("**DEBUG**");
        puts("Function name: writefile");
        printf("Parameters: start = %u, filename = %s, ", start, filename);
        puts("");
        puts("");
    }

    strncpy(file, filename, 99);
    outfilebuffer = fopen(file, "w");
    if (errno == 2) {
        errno = 0;
    }

    if (outfilebuffer != NULL) {
        if ((start) == NULL) {

        } else if ((start) != NULL) {
            struct record * currentRecord;
            currentRecord = start;

            while (currentRecord != NULL) {
                fprintf(outfilebuffer, "%i\n", (*currentRecord).accountno);
                fprintf(outfilebuffer, "%s\n", (*currentRecord).name);
                fprintf(outfilebuffer, "%s^\n", (*currentRecord).address);
                fprintf(outfilebuffer, "%i\n", (*currentRecord).yearofbirth);
                currentRecord = (*currentRecord).next;
            }
        }
        fclose(outfilebuffer);
    } else {
        perror("\n(File could not be opened)");
    }

}
