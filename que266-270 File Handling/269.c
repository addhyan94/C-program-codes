/*Take name and salary of two employees as input from the user and write them to a text file in the following format:
i. Name1, 3300
ii. Name2, 7700*/
#include<stdio.h>
void main()
{
FILE *fptr;
int salary1,salary2;
char ename1[50],ename2[50];
fptr = fopen("salary.txt","w");

printf("Enter the Name of First Employe : ");
scanf("%s",&ename1);

printf("Enter the Salary : ");
scanf("%d",&salary1);

printf("\nEnter the Name of Second Employe : ");
scanf("%s",&ename2);

printf("Enter the Salary : ");
scanf("%d",&salary2);

fprintf(fptr ,"%s", ename1);
fprintf(fptr ,"%s", " , ");
fprintf(fptr ,"%d", salary1);
fprintf(fptr ,"%c", '\n');

fprintf(fptr ,"%s", ename2);
fprintf(fptr ,"%s", " , ");
fprintf(fptr ,"%d", salary2);

fclose(fptr);
printf("\nCompleted....");
}