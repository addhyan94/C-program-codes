//              File Handling 

// WAP read a text file character by character and write its content twice in separate file.
#include<stdio.h>
void main()
{
char ch;
FILE *fptr;
FILE *fptr2;

fptr = fopen("A3File.txt","r");
fptr2 = fopen("A3File.1.txt","w");
while (1)
{
ch=fgetc(fptr);
if (ch == EOF)
{
    printf("\nCompleted");
    break;
}
else
{
    fprintf(fptr2, "%c",ch);
    fprintf(fptr2, "%c",ch);
    printf("%c",ch);
}
}
fclose(fptr);
fclose(fptr2);
}