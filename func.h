/*****************************************************************
 // Name:        Wyatt Bartlett
 //
 // Homework:    Project 1
 //
 // Class:       ICS 212
 //
 // Instructor:  Ravi Narayan
 //
 // Date:        March 16, 2016
 //
 // File:        func.h
 //
 // Description: The file contains the prototypes for the Project 1 functions.
 //
 //***************************************************************/

int addRecord(struct record **, int, char[], char[], int);
int printRecord(struct record *, int);
int modifyRecord(struct record *, int, char[]);
void printAllRecords(struct record *);
int deleteRecord(struct record **, int);
void cleanup(struct record *);

void checkDebugMode(int, char**);
int isListEmpty(struct record *);
void displayMenu();
int getChoice();
int getAccountNo();
void getName(char[], int);
void getfield(char[], int);
int getBirthYear();
void chooseField(char[], char[], char[]);
void removeTrailingSpace(char string[]);
void eatTrash();

int readfile(struct record **, char[]);
void writefile(struct record *, char[]);
