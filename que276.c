//                             Function Overloding
//WAP to input 3 number calculate sum of 2 number and sum of 3 number using function overloding.
#include<stdio.h>
#include<conio.h>
int sum(int,int);
int sum(int,int,int);
int main()
{
    int a,b,c;
    printf("Enter the First Number: ");
    scanf("%d",&a);
    printf("Enter the Second Number: ");
    scanf("%d",&b);
    printf("Enter the Third Number: ");
    scanf("%d",&c);
    printf("Sum of 2 Number is : %d",sum(a,b));
    printf("\nSum of 3 Number is : %d",sum(a,b,c));
}