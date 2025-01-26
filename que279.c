//                             Function Overloding
// WAP to input base and height for one triangle and input length of 3 sides for other triangle calculate area of both triangle using function overloading.
#include<stdio.h>
#include<conio.h>
int area(int,int);
int area(int,int,int);
int main()
{
    int b,h,s1,s2,s3;
    printf("Enter the Base of Triangle: ");
    scanf("%d",&b);
    printf("Enter the Height of Triangle: ");
    scanf("%d",&h);
    printf("Enter the Length of 1st Side of Triangle: ");
    scanf("%d",&s1);
    printf("Enter the Length of 2nd Side of Triangle: ");
    scanf("%d",&s2);
    printf("Enter the Length of 3rd Side of Triangle: ");
    scanf("%d",&s3);
    printf("Area of Triangle with Base and Height is : %d",area(b,h));
    printf("\nArea of Triangle with 3 Sides is : %d",area(s1,s2,s3));
}