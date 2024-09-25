#define _GNU_SOURCE		//strcasestr is a nonstandard GNU extension, 
//we need this line while serching for matching last name
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"
////////////////////////////////////////////////////////////////////////
//
// File           : p2-support.c
// Description    : All the function definistions for project2 
// Author         : Trevor Eby
// Date           : 11/3/23
// Notes          : - Fix delId and searchId
//                

int compareIDs(const void* firstId, const void* secondId) {
    struct Employee* one = (struct Employee*)firstId;
    struct Employee* two = (struct Employee*)secondId;
    return strcmp(one->ID, two->ID);
}

int compareDates(const void* firstDate, const void* secondDate){
  struct Employee* one = (struct Employee*)firstDate;
  struct Employee* two = (struct Employee*)secondDate;
  if (one->hire_date.year < two->hire_date.year) {
    return -1;
  } 
  else if (one->hire_date.year > two->hire_date.year) {
    return 1;
  }
  if (one->hire_date.month < two->hire_date.month) {
    return -1;
  }
  else if (one->hire_date.month > two->hire_date.month) {
    return 1;
  }
  if (one->hire_date.day < two->hire_date.day) {
    return -1;
  } 
  else if (one->hire_date.day > two->hire_date.day) {
    return 1;
  }
  return 0;
}

void sortID(dataBase_ptr db){
	qsort(&(db->emp[1]), db->total, sizeof(struct Employee), compareIDs);
}

void sortHireDate(dataBase_ptr db){
	qsort(&(db->emp[1]), db->total, sizeof(struct Employee), compareDates);
}

void displayhelper(dataBase_ptr db, int i){
  char reset[(nameSIZE * 3)] = "";
  //char name[(strlen(db->emp[i].first_name) + strlen(db->emp[i].last_name) + 1)];
  char name[(nameSIZE * 3)];
  strcpy(name, reset);
  strcat(name, db->emp[i].first_name);
  strcat(name, " ");
  strcat(name, db->emp[i].last_name);
  
  if(i-1 < 10){
    printf("%d   ", i-1);
  }
  else if(i-1>=10 && i-1<=99){
    printf("%d  ", i-1);
  }
  else{
    printf("%d ", i-1);
  }
	printf("%s", db->emp[i].ID);
  printf(" ");
  printf("%.13s", name);
  for(int i = strlen(name); i < 13; i++){
    printf(" ");
  }
  printf(" ");
  char elen[strlen(db->emp[i].email)];
  strcpy(elen, reset);
  strcat(elen, db->emp[i].email);
  printf("%.12s", elen);
  if(strlen(elen) > 12){
    printf(" ");
  }
  else{
    for (int i = strlen(elen); i<=12; i++){
      printf(" ");
    }
  }
  
    //strcpy(elen, reset);
  printf("$");
  printf("%9.2f", db->emp[i].salary);
  printf(" ");
  printf("%.2d", db->emp[i].hire_date.month);
  printf("/");
  printf("%.2d", db->emp[i].hire_date.day);
  printf("/");
  printf("%.2d", db->emp[i].hire_date.year);
  printf("\n");
}

void  display_emp(dataBase_ptr db){
  print_title();
  //char reset[nameSIZE * 2] = "";
	for(int i = 1; i <= db->total; i++){
    displayhelper(db, i);
	}
}

void searchID(dataBase_ptr db){
  char id[idSIZE*2];
  char realId[idSIZE*2] = "";
  //char reset[nameSIZE * 2] = "";
  printf("Enter the ID you are searching for\n");
	scanf("%s", id);
  if(strlen(id) == 1){
    strcat(realId, "0000");
    strcat(realId, id);
  }
  else if(strlen(id) == 2){
    strcat(realId, "000");
    strcat(realId, id);
  }
  else {
    strcat(realId, "00");
    strcat(realId, id);
  }
  int found = -1;
  print_title();
	for(int i = 1; i <= db->total; i++){
		if(strcmp(db->emp[i].ID, realId) == 0){
      displayhelper(db, i);
      found = i;
		}
	}
  if(found == -1){
    printf("No employee with that ID found in the database.");
  }
}

void searchLastName(dataBase_ptr db){
  char lastname[nameSIZE*2];
  char compName[nameSIZE*2];
  char reset[nameSIZE*2] = "";
  printf("Enter the Last Name you are searching for\n");
	scanf("%s", lastname);
  int found = -1;
  //strcpy(lastname, strlwr(lastname));
  int length = strlen(lastname);

	for(int i = 1; i <= db->total; i++){
    strcpy(compName, reset);
    strncpy(compName, db->emp[i].last_name, length);
		if(strcasestr(compName, lastname) != 0){
      if(found == -1){
        print_title();
      }
      displayhelper(db, i);
      found = i;
		}
	}
  if(found == -1){
    printf("No employee with that last name found in the database.");
  }
}

void delID(dataBase_ptr db){
  char id[idSIZE*2];
  char realId[idSIZE*2] = "";
  printf("Enter the ID you are searching for\n");
  scanf("%s", id);
  if(strlen(id) == 1){
    strcat(realId, "0000");
    strcat(realId, id);
  }
  else if(strlen(id) == 2){
    strcat(realId, "000");
    strcat(realId, id);
  }
  else {
    strcat(realId, "00");
    strcat(realId, id);
  }
  int found = -1;
  
  for(int i = 1; i <= db->total; i++){
		if(strcmp(db->emp[i].ID, realId) == 0){
      printf("The following employee is deleted:\n");
      print_title(db);
      displayhelper(db, i);
			//free(db->emp[i]);
      //db->emp[i] = NULL;
      strcpy(db->emp[i].ID, "");
      strcpy(db->emp[i].first_name, "");
      strcpy(db->emp[i].last_name, "");
      strcpy(db->emp[i].email, "");    
      db->emp[i].salary = 0;
      db->emp[i].hire_date.day = 0;
      db->emp[i].hire_date.month = 0;
      db->emp[i].hire_date.year = 0;
      for(int j = i; j <= db->total; j++){
        strcpy(db->emp[j].ID, db->emp[j + 1].ID);
        strcpy(db->emp[j].first_name, db->emp[j + 1].first_name);
        strcpy(db->emp[j].last_name, db->emp[j + 1].last_name);
        strcpy(db->emp[j].email, db->emp[j + 1].email);
        db->emp[j].salary = db->emp[j + 1].salary;
        db->emp[j].hire_date = db->emp[j + 1].hire_date;
      }
      db->total = db->total - 1;
      found = i;
      save(db);
		}
	}
  
  if(found == -1){
    printf("No employee with that ID found in the database.");
  }
}

void create_record(char id[], char firstname[], char lastname[], char email[], double salary, date hire_date, dataBase_ptr db)// specify parameters. Clues are in the initalize function.
{
  db->total += 1;
  strcpy(db->emp[db->total].ID, id);
  strcpy(db->emp[db->total].first_name, firstname);
  strcpy(db->emp[db->total].last_name, lastname);
  strcpy(db->emp[db->total].email, email);    
  db->emp[db->total].salary = salary;
  db->emp[db->total].hire_date = hire_date;
  //define function. Clues are in the initalize function
  //do not forget to increase total number of employees in the database
}

void print_title ()// you can keep this fuction or remove if needed
{
  printf ("No. ID    Name          Email        Salary     Hire Date\n");
  printf ("--- ----- ------------- ------------ ---------- --/--/----\n");
}

//fix save function. Save array into file: database_updated in the same format with the 
//database file.
void save (dataBase_ptr db)// this function is for saving the database into a text file
{
  FILE *dbfu;
  dbfu = fopen ("database_updated", "w");//open an Std IO file to write into
  if (dbfu == NULL)
  {
    printf ("File cannot be created");
    return;
  }
  for (int i = 1; i <= db->total; i++)
  {
      fprintf (dbfu,"%s ", db->emp[i].ID);
      //add format specifiers here, db->emp[i].ID,
	    //add other members);
      fprintf(dbfu,"%s ", db->emp[i].first_name);
      fprintf(dbfu,"%s ", db->emp[i].last_name);
      fprintf(dbfu,"%s ", db->emp[i].email);
      //if(sizeof(db->emp[i].salary) < 9){
        //fprintf(dbfu,"%.2f ", db->emp[i].salary);
      //}
      fprintf(dbfu,"%.2f ", db->emp[i].salary);
      fprintf(dbfu,"%d/", db->emp[i].hire_date.month);
      fprintf(dbfu,"%d/", db->emp[i].hire_date.day);
      fprintf(dbfu,"%d", db->emp[i].hire_date.year);
      fprintf(dbfu, "\n");
  }
  fclose (dbfu);//close file after writing
  return;
}

void display_menu (struct DataBase *db)
{
  int input = 0;
  while (input != 8)
  {
    puts
      ("\n**************************************************************");
    printf
      (  "********** Employee Database - Total Employees: %03d **********\n", db->total);//you need to fix this line so that total employees in the database is printed
    puts
      ("**************************************************************\n");
    puts ("Choose one of the menu options below:");
    puts ("1. Sort by ID");
    puts ("2. Sort by Hire Date");
    puts ("3. Display all employees");
    puts ("4. Search employees by ID");
    puts ("5. Search employees by Last Name");
    puts ("6. Delete employee by ID");
    puts ("7. Save");
    puts ("8. Exit");

    scanf ("%d", &input);

    switch (input)
    {
      case 1:
        //call the function you defined for sorting by ID
        sortID(db);
        break;
      case 2:
        //call the function you defined for sorting by Hire Date
        sortHireDate(db);
        break;
      case 3:
        //call the function you defined for displaying employees
        display_emp(db);
        break;
      case 4:
        //call the function you defined for searching employees by ID
        searchID(db);
        break;
      case 5:
        //call the function you defined for searching employees by Last Name
        searchLastName(db);
        break;
      case 6:
        //call the function you defined for deleting employee by ID
        delID(db);
        break;
      case 7:
        save (db);
        break;
     case 8:
        //free all allocated memory
        free(db->emp);
        free(db);
        printf("Bye!\n");
        //exit(0);
        //exit(db);
        break;
    }
  }
}