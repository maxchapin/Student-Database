//Maxwell Chapin
//April 8, 2021
//CS-282 - Programming Project 4
//Create a linkedlist of students and their information
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>

void insertStudentNode();
void printStudentNodes();
void countStudentNodes();
void deleteStudentNode();
void modifyStudentNode();
struct student *getStudentNode();;

struct date *getRegDate();

struct date
{
    int day, month, year;

};
     int validateDateOfReg(struct date *d1);

struct student
{
    int studentId;

    char studentName[30];

    float gpa;

    struct date dt_of_reg;

    struct student *next;
};
struct student *start;

int main(){

    start = NULL; //Empty Linked List
    int choice = 0;

    char run = 'Y';
    while(run == 'y' || run == 'Y'){
        printf("\nStudents Records Operations - Menu Option");
        printf("\n******************************");
        printf("\n1. Insert a New Student Record");
        printf("\n2. Print all Student Records");
        printf("\n3. Delete a Student Record");
        printf("\n4. Count Student Records");
        printf("\n5. Modify a Student Record");
        printf("\n6. Quit");
        printf("\n Enter Choice(1-6): ");

        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);
        printf("\n");
        switch(choice){
            case 1: insertStudentNode();
            break;
            case 2: printStudentNodes();
            break;
            case 3: deleteStudentNode();
            break;
            case 4: countStudentNodes();
            break;
            case 5: modifyStudentNode();
            break;
            case 6: run = "n";
         }
    }
}

struct student *getStudentNode(){



     struct student *new;
     new = (struct student*)malloc(sizeof(struct student));
     if (new == NULL)
        printf("\nMemory Error!!\n");

     printf("\nEnter the ID of the new Student: ");
     scanf("%d", &new->studentId);
     fflush(stdin);

     printf("\nEnter the name of the new Student: ");
     scanf("%s", &new->studentName);
     fflush(stdin);

     printf("\nEnter the GPA of the new Student: ");
     scanf("%f", &new->gpa);
     fflush(stdin);

     printf("\nEnter the Date of Registration of the new Student: ");
     scanf("%d/%d/%d", &new->dt_of_reg.month, &new->dt_of_reg.day, &new->dt_of_reg.year );
     while(validateDateOfReg(&new->dt_of_reg) != 1){
        printf("\nEnter the Date of Registration of the new Student: ");
        scanf("%d/%d/%d", &new->dt_of_reg.month, &new->dt_of_reg.day, &new->dt_of_reg.year );
     }

     new -> next = NULL;
     return(new);

}

//Gets the values of the student's registration date
struct date *getRegDate(){

    struct date *dt;
    dt = (struct date*)malloc(sizeof(struct date));
    if (dt == NULL)
        printf("\nMemory Error!!\n");

    scanf("%d/%d/%d", &dt->month, &dt->day, &dt->year );
    if(validateDateOfReg(dt) == 1){
            printf("Good Date");
        return(dt);
    }
    else{
         printf("Bad Date");
        getRegDate();
    }
};

  int validateDateOfReg(struct date *dt){
    SYSTEMTIME t;
    GetLocalTime(&t);

    printf("\nDate being checked: Year: %d Month: %d Day: %d\n", dt->year, dt->month, dt->day);

    if ((dt->month > 12 || dt->month < 0 ) || ( dt->day > 31 || dt->day < 0 ) ||
    ( dt->year > t.wYear || dt->year < 2010 ) )
    {
        printf ( "\nImproper date entered" ) ;
        return 0;
    }
    else{
        if(dt->year == t.wYear){
            if(dt->month > t.wMonth)
                printf ( "\nImproper date entered" ) ;
                return 0;
            if(dt->month == t.wMonth && dt->day > t.wDay){
                printf( "\nImproper date entered");
                return 0;
            }
        }
        else{
            printf("Good date");
            return 1;
        }

    }


}

//Adds a new node in the sorted LinkedList in ascending order
void insertStudentNode()
{
     struct student *getStudentNode();
     struct student *ptr, *new, *prev;
     new = getStudentNode();
     if (start == NULL){
         start = new;
         return;
     }

     for(ptr = start; (ptr)&& ((new->studentId) > (ptr->studentId)); prev = ptr, ptr = ptr -> next);
     if (ptr!=start){
         prev -> next = new;
         new -> next = ptr;
     }
     else
     {
        new -> next = start;
        start = new;
     }
     return;
}

//Deletes a node from the list
void deleteStudentNode()
{
     struct student *prev, *currPtr;
     if (start == NULL)
        printf("\n List does not contain data.\n");
     else{
         int key;
         printf("\nPlease enter the value you wish to delete (Only first occurrence will be deleted): ");
         scanf("%d", &key);
         fflush(stdin);

         //Traverse the list and keep comparing the values
         for(currPtr = start; (currPtr)&& ((currPtr->studentId) != key); prev = currPtr, currPtr = currPtr -> next);
             if (currPtr == NULL)
                printf("\nItem not Found");
             else{
                if(currPtr == start){
                     start = currPtr -> next;
                     free(currPtr);
                 }
                 else{ //Node to be deleted is somewhere in the middle or at the end of the list
                     prev -> next = currPtr -> next;
                     free(currPtr);
                 }
             }
     }
}

/*Prints the contents of the linked list*/
void printStudentNodes()
{
     struct student *ptr;
     if (start == NULL)
        printf("\n List does not contain data.\n");
     else
         for(ptr = start; ptr; ptr = ptr -> next)
            printf("Student ID: %d \nStudent Name: %s \nGPA: %.2f \nDate of Registration: %d/%d/%d\n", ptr -> studentId, ptr -> studentName, ptr -> gpa, ptr -> dt_of_reg.month, ptr -> dt_of_reg.day, ptr -> dt_of_reg.year);

}


/*Function that counts the amount of nodes in the list*/
void countStudentNodes()
{
     int count = 0;
     struct student *ptr;
     if (start == NULL)
        printf("\n List does not contain data.\n");
     else{
         for(ptr = start; ptr; ptr = ptr -> next, count++);
         printf("\nThis linked list has %d node(s).\n\n", count);
     }
}

void modifyStudentNode(){

 struct student *new;
 new = (struct student*)malloc(sizeof(struct student));
 if (new == NULL)
 printf("\nMemory Error!!\n");

 int modifyId;
 char newStudentName[30];
 float newGpa;
 struct date newDt_of_reg;

 printf("\nPlease enter the Student ID you wish to modify: ");
 scanf("%d", &modifyId);
 fflush(stdin);

 printf("\nEnter modified Student Name: ");
 scanf("%s", &newStudentName);
 fflush(stdin);

 printf("\nEnter the GPA of the new Student: ");
 scanf("%f", &newGpa);
 fflush(stdin);

 printf("\nEnter the Date of Registration of the new Student: ");
 //getRegDate -> dt_of_reg;
 fflush(stdin);

 while(start->next!=NULL) {
      if(start->studentId == modifyId) {

         start->gpa = newGpa;
         //start->dt_of_reg = newStudentName;
         return;
      }

      start = start->next;
   }
 return(new);

}
