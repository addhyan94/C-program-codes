//                             Function Overloding
//WAP to input L,B of a rectangle and R fo a circle calculate area of recrangle and circle using function overloding.
#include<stdio.h>
#include<conio.h>
int area(int,int);
int area(int);
int main()
{
    int l,b,r;
    printf("Enter the Length of Rectangle: ");
    scanf("%d",&l);
    printf("Enter the Breadth of Rectangle: ");
    scanf("%d",&b);
    printf("Enter the Radius of Circle: ");
    scanf("%d",&r);
    printf("Area of Rectangle is : %d",area(l,b));
    printf("\nArea of Circle is : %d",area(r));
}