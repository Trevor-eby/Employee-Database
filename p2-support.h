////////////////////////////////////////////////////////////////////////
//
// File           : p2-support.h
// Description    : Header file for project2 
// Author         : Trevor Eby
// Date           : 11/3/23
// Notes          : ***Type bug fixes/other with dates for your records
//                

#ifndef P2Header //To prevent double inclusion of header
#define P2Header //To prevent double inclusion of header

#include <stdio.h>
#define byID 1
#define byNAME 2
#define dbSIZE 100
#define idSIZE 6
#define nameSIZE 10
#define emailSIZE 20


typedef struct date// do not modify
{
  int day; 
  int month;
  int year;
}date;

typedef struct Employee
{
  char ID[idSIZE];
  char first_name[nameSIZE];
  char last_name[nameSIZE];
  char email[emailSIZE];
  double salary;
  date hire_date;
  //declare other members
}employee, *employee_ptr;

typedef struct DataBase
{
  //a pointer to first element of empoloyee array
  struct Employee* emp;
  //number of employees in database
  int total;
}*dataBase_ptr;

// Functional Prototypes

// Function     : initialize
// Description  : This function creates an array in the database
//                then initalializes each array elemet with the data 
//                in the given file
// Inputs       : a pointer to DataBase struct
// Output       : none
void initialize (dataBase_ptr);

//Write formal comments for each function header. 
//In the same format with the initialize function

// Function     : create_record
// Description  : This function creates a new employee and gets user input for all the variables that make up an employee.
// Inputs       : 4 character strings for the ID, first name, last name, and email
//                1 double for salary, a date for the hiring date, and a pointer to DataBase structure.
// Output       : none
void create_record (char[], char[], char[], char[], double, date, dataBase_ptr);//specify parameters types. Clues are in the initalize function.

// Function     : print_title
// Description  : prints a description of what input formatting should look like
// Inputs       : none
// Output       : none
void print_title ();

// Function     : display_menu
// Description  : Gets user input and calls all the functions that alter the DataBase and gives info about the DataBase.
// Inputs       : a pointer to DataBase struct
// Output       : none
void display_menu (dataBase_ptr);

//other function headers here

// Function     : save
// Description  : This function writes to a file all the information that is wanted to be saved about each employee.
// Inputs       : a pointer to DataBase struct
// Output       : none
void save(dataBase_ptr);

// Function     : sortID
// Description  : This function sorts the DataBase by ID number
// Inputs       : a pointer to DataBase struct
// Output       : none
void sortID(dataBase_ptr);

// Function     : sortHireDate
// Description  : This function sorts the DataBase by hire dates.
// Inputs       : a pointer to DataBase struct
// Output       : none
void sortHireDate(dataBase_ptr);

// Function     : display_emp
// Description  : This function displays all the information about all the employee
// Inputs       : a pointer to DataBase struct
// Output       : none
void display_emp(dataBase_ptr);

// Function     : searchID
// Description  : This function will search the database for an employee based on their ID and print out all their information.
// Inputs       : a pointer to DataBase struct
// Output       : none
void searchID(dataBase_ptr);

// Function     : searchLastName
// Description  : This function searches the database for an employee based on their last name and will print out all their information.
// Inputs       : a pointer to DataBase struct
// Output       : none
void searchLastName(dataBase_ptr);

// Function     : delID
// Description  : This function deletes an employee from the DataBase
// Inputs       : a pointer to DataBase struct
// Output       : none
void delID(dataBase_ptr);

// Function     : displayhelper
// Description  : This function does all the printing for an employee's information.
// Inputs       : a pointer to DataBase struct and an integer
// Output       : none
void displayhelper(dataBase_ptr, int);

// Function     : compareIDs
// Description  : This function compares ID values of employees
// Inputs       : two void pointers
// Output       : none
int compareIDs(const void*, const void*);

// Function     : compareDates
// Description  : This function compares dates of employees
// Inputs       : two void pointers
// Output       : none
int compareDates(const void*, const void*);

#endif //To prevent double inclusion of header
